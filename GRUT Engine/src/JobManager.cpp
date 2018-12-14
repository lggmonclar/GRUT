#include "grutpch.h"
#include "JobManager.h"

namespace GRUT {
	/*Private:*/
	JobManager::JobManager() {
		LaunchThreads();
	}
	void JobManager::LaunchThreads() {
		unsigned coresAvailable = std::thread::hardware_concurrency();

		for (unsigned j = 0; j < FIBER_COUNT_PER_THREAD * coresAvailable; ++j) {
			m_fibers.emplace_back(CreateFiber(0, &FiberEntryPoint, nullptr));
		}

		for (unsigned i = 0; i < coresAvailable; ++i) {
			m_threads.emplace_back(std::thread([=] {
				SetThreadAffinityMask(GetCurrentThread(), 1i64 << i);
				m_threadHasSwitchSL[std::this_thread::get_id()] = false;
				ConvertThreadToFiber(nullptr);
				YieldFiber(false);
			}));
		}
	}
	JobManager::~JobManager() {
		m_threadsSpinLock.Acquire();
		for (auto &t : m_threads) {
			t.join();
		}
		m_threadsSpinLock.Release();
	}

	void JobManager::LockFiberSwitchLock() {
		if (!m_threadHasSwitchSL[std::this_thread::get_id()]) {
			m_fiberSwitchSpinLock.Acquire();
			m_threadHasSwitchSL[std::this_thread::get_id()] = true;
		}
	}

	void JobManager::UnlockFiberSwitchLock() {
		if (m_threadHasSwitchSL[std::this_thread::get_id()]) {
			m_threadHasSwitchSL[std::this_thread::get_id()] = false;
			m_fiberSwitchSpinLock.Release();
		}
	}

	void __stdcall JobManager::FiberEntryPoint(void *p_lpParameter) {
		while (true) {
			Instance().UnlockFiberSwitchLock();
			auto job = JobManager::Instance().FetchJob();

			if (job) {
				job->m_associatedFiber = GetCurrentFiber();
				job->m_entryPoint(job);
				job->m_isDone = true;
				Instance().AwakenWaitingFibers(job.get());
			}
			else {
				Instance().YieldFiber();
			}
		}
	}

	void JobManager::YieldFiber(const bool p_insertSelfIntoList) {
		LockFiberSwitchLock();
		auto nextFiber = m_fibers[0];
		m_fibers.pop_front();
		if (p_insertSelfIntoList) {
			m_fibers.emplace_back(GetCurrentFiber());
		}
		SwitchToFiber(nextFiber);
		UnlockFiberSwitchLock();
	}

	/*Public:*/
	std::shared_ptr<Job> JobManager::FetchJob(JobPriority p_priority) {
		std::shared_ptr<Job> job = nullptr;

		m_fetchJobSpinLock.Acquire();
			if (p_priority > JobPriority::HIGH && m_criticalPJobs.size() > 0) {
				job = m_criticalPJobs.front();
				m_criticalPJobs.pop();
			}
			else if (p_priority > JobPriority::NORMAL && m_highPJobs.size() > 0) {
				job = m_highPJobs.front();
				m_highPJobs.pop();
			}
			else if (p_priority > JobPriority::LOW && m_normalPJobs.size() > 0) {
				job = m_normalPJobs.front();
				m_normalPJobs.pop();
			}
			else if (m_lowPJobs.size() > 0) {
				job = m_lowPJobs.front();
				m_lowPJobs.pop();
			}
		m_fetchJobSpinLock.Release();

		return job;
	}

	std::weak_ptr<Job> JobManager::KickJob(Job &&p_jobDecl) {
		std::shared_ptr<Job> ref = std::make_shared<Job>(std::move(p_jobDecl));
		m_fetchJobSpinLock.Acquire();
		switch (p_jobDecl.m_priority) {
			case JobPriority::CRITICAL:
				m_criticalPJobs.push(ref);
				break;
			case JobPriority::HIGH:
				m_highPJobs.push(ref);
				break;
			case JobPriority::NORMAL:
				m_normalPJobs.push(ref);
				break;
			case JobPriority::LOW:
			default:
				m_lowPJobs.push(ref);
				break;
		}
		m_fetchJobSpinLock.Release();
		return ref;
	}

	void JobManager::PlaceFiberOnWaitList(const std::weak_ptr<Job> &p_jobToWaitOnWeakPtr, Job * const p_waiterJob) {
		LockFiberSwitchLock();

		auto jobToWaitOn = p_jobToWaitOnWeakPtr.lock();
		if (!jobToWaitOn || jobToWaitOn->m_isDone) {
			UnlockFiberSwitchLock();
			return;
		}

		p_waiterJob->m_counter++;

		auto search = m_waitList.find(jobToWaitOn.get());
		if (search != m_waitList.end()) {
			search->second.emplace_back(p_waiterJob);
		}
		else {
			m_waitList[jobToWaitOn.get()] = { p_waiterJob };
		}

		YieldFiber(false);
	}

	void JobManager::PlaceFibersOnWaitList(const std::vector<std::weak_ptr<Job>> &p_jobsToWaitOnWeakPtrs, Job * const p_waiterJob) {
		LockFiberSwitchLock();

		std::vector<std::shared_ptr<Job>> availablePtrs;
		for (auto &weakJobPtr : p_jobsToWaitOnWeakPtrs) {
			auto jobPtr = weakJobPtr.lock();
			if (jobPtr && !jobPtr->m_isDone)
				availablePtrs.emplace_back(jobPtr);
		}

		for (auto &job : availablePtrs) {
			if (job->m_isDone) continue;

			p_waiterJob->m_counter++;
			auto search = m_waitList.find(job.get());
			if (search != m_waitList.end()) {
				search->second.emplace_back(p_waiterJob);
			}
			else {
				m_waitList[job.get()] = { p_waiterJob };
			}
		}

		if (p_waiterJob->m_counter == 0) {
			UnlockFiberSwitchLock();
			return;
		}

		YieldFiber(false);
	}

	void JobManager::AwakenWaitingFibers(Job * const p_job) {
		LockFiberSwitchLock();

		auto search = m_waitList.find(p_job);
		if (search != m_waitList.end()) {
			for (auto &job : search->second) {
				if (--job->m_counter == 0) {
					if (job->m_associatedFiber != GetCurrentFiber()) {
						m_fibers.emplace_back(job->m_associatedFiber);
					}
				}
			}
			m_waitList.erase(p_job);
		}

		YieldFiber();
	}
}
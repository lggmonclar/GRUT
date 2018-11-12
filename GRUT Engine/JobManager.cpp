#include "JobManager.h"
#include <iostream>

namespace GRUT {
	/*Private:*/
	JobManager::JobManager() {
		LaunchThreads();
	}
	const void JobManager::LaunchThreads() {
		ConvertThreadToFiber(nullptr);
		unsigned coresAvailable = std::thread::hardware_concurrency();
		for (unsigned int i = 0; i < coresAvailable; ++i) {
			for (int j = 0; j < FIBER_COUNT_PER_THREAD; ++j) {
				std::unique_ptr<Fiber::Data> fData(std::make_unique<Fiber::Data>());
				fData->m_fiberAddr = CreateFiber(0, &Fiber::WaitForJob, *fData);
				m_fibers.push_back(std::move(fData));
			}

			m_threads.push_back(std::thread([=] {
				SetThreadAffinityMask(GetCurrentThread(), 1 << i);
				ConvertThreadToFiber(nullptr);
				SwitchToFiber(m_fibers[i]->m_fiberAddr);
			}));
		}
	}
	JobManager::~JobManager() {
		for (auto &t : m_threads) {
			t.join();
		}
	}
	/*Public:*/
	std::optional<Job::Declaration> JobManager::FetchJob(Job::Priority p_priority) {
		Job::Declaration job;
		if (p_priority > Job::Priority::HIGH && m_criticalPJobs.size() > 0) {
			job = m_criticalPJobs.front();
			m_criticalPJobs.pop();
		}
		else if (p_priority > Job::Priority::NORMAL && m_highPJobs.size() > 0) {
			job = m_highPJobs.front();
			m_highPJobs.pop();
		}
		else if (p_priority > Job::Priority::LOW && m_normalPJobs.size() > 0) {
			job = m_normalPJobs.front();
			m_normalPJobs.pop();
		}
		else if (m_lowPJobs.size() > 0) {
			job = m_lowPJobs.front();
			m_lowPJobs.pop();
		}

		if (job.m_entryPoint != nullptr) return job;
		return {};
	}

	void JobManager::KickJob(const Job::Declaration &p_jobDecl) {
		switch (p_jobDecl.m_priority) {
			case Job::Priority::CRITICAL:
				m_criticalPJobs.push(p_jobDecl);
				break;
			case Job::Priority::HIGH:
				m_highPJobs.push(p_jobDecl);
				break;
			case Job::Priority::NORMAL:
				m_normalPJobs.push(p_jobDecl);
				break;
			case Job::Priority::LOW:
			default:
				m_lowPJobs.push(p_jobDecl);
				break;
		}
	}
}
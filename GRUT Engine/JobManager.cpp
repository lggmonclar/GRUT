#include "JobManager.h"
#include <iostream>

namespace GRUT {
	/*Private:*/
	JobManager::JobManager() {
		LaunchThreads();
	}
	const void JobManager::LaunchThreads() {
		unsigned coresAvailable = std::thread::hardware_concurrency();
		for (unsigned i = 0; i < coresAvailable; ++i) {
			m_threads.push_back(std::thread([&, i] {
				m_launchThreadsSpinLock.Acquire();
				{
					SetThreadAffinityMask(GetCurrentThread(), 1 << i);
					std::unique_ptr<Fiber::Data> baseFiberData(std::make_unique<Fiber::Data>());
					baseFiberData->m_fiberAddr = ConvertThreadToFiber(nullptr);
					m_fibers.push_back(std::move(baseFiberData));
					Fiber::WaitForJob(*baseFiberData);

					for (unsigned j = 0; j < FIBER_COUNT_PER_THREAD; ++j) {
						std::unique_ptr<Fiber::Data> fData(std::make_unique<Fiber::Data>());
						fData->m_fiberAddr = CreateFiber(0, &Fiber::WaitForJob, *fData);
						m_fibers.push_back(std::move(fData));
					}
				}
				m_launchThreadsSpinLock.Release();
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
		std::optional<Job::Declaration> job;

		m_fetchJobSpinLock.Acquire();
		{
			if (p_priority > Job::Priority::HIGH && m_criticalPJobs.size() > 0) {
				job = std::move(m_criticalPJobs.front());
				m_criticalPJobs.pop();
			}
			else if (p_priority > Job::Priority::NORMAL && m_highPJobs.size() > 0) {
				job = std::move(m_highPJobs.front());
				m_highPJobs.pop();
			}
			else if (p_priority > Job::Priority::LOW && m_normalPJobs.size() > 0) {
				job = std::move(m_normalPJobs.front());
				m_normalPJobs.pop();
			}
			else if (m_lowPJobs.size() > 0) {
				job = std::move(m_lowPJobs.front());
				m_lowPJobs.pop();
			}
		}
		m_fetchJobSpinLock.Release();

		return job;
	}

	void JobManager::KickJob(Job::Declaration &&p_jobDecl) {

		m_fetchJobSpinLock.Acquire(); 
		{
			switch (p_jobDecl.m_priority) {
				case Job::Priority::CRITICAL:
					m_criticalPJobs.push(std::move(p_jobDecl));
					break;
				case Job::Priority::HIGH:
					m_highPJobs.push(std::move(p_jobDecl));
					break;
				case Job::Priority::NORMAL:
					m_normalPJobs.push(std::move(p_jobDecl));
					break;
				case Job::Priority::LOW:
				default:
					m_lowPJobs.push(std::move(p_jobDecl));
					break;
			}
		}
		m_fetchJobSpinLock.Release();
	}
}
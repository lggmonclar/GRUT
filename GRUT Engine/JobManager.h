#pragma once
#include <windows.h>
#include <thread>
#include <vector>
#include <queue>
#include <optional>
#include <map>
#include "Job.h"
#include "SpinLock.h"

constexpr unsigned FIBER_COUNT_PER_THREAD = 8;

namespace GRUT {
	class JobManager {
	private:
		SpinLock m_fetchJobSpinLock;
		SpinLock m_fiberSwitchSpinLock;
		SpinLock m_threadsSpinLock;
		
		std::map<Job*, std::vector<Job*>> m_waitList;
		std::deque<void *> m_fibers;
		std::vector<std::thread> m_threads;
		std::map<std::thread::id, bool> m_threadHasSwitchSL;

		std::queue<std::shared_ptr<Job>> m_criticalPJobs;
		std::queue<std::shared_ptr<Job>> m_highPJobs;
		std::queue<std::shared_ptr<Job>> m_normalPJobs;
		std::queue<std::shared_ptr<Job>> m_lowPJobs;
		static void __stdcall FiberEntryPoint(void * p_lpParameter);
		void LaunchThreads();
		void LockFiberSwitchLock();
		void UnlockFiberSwitchLock();
		void YieldFiber(const bool p_insertSelfIntoList = true);
	protected:
		JobManager();
		~JobManager();
	public:
		JobManager(JobManager const &) = delete;
		JobManager& operator=(JobManager const &) = delete;
		static JobManager& Instance() {
			static JobManager instance{};
			return instance;
		}
		std::shared_ptr<Job> FetchJob(JobPriority p_priority = JobPriority::LOW);
		std::weak_ptr<Job> KickJob(Job &&p_jobDecl);
		void PlaceFiberOnWaitList(const std::weak_ptr<Job> &p_jobToWaitOnWeakPtr, Job *p_waiterJob);
		void PlaceFibersOnWaitList(const std::vector<std::weak_ptr<Job>> &p_jobsToWaitOnWeakPtrs, Job *p_waiterJob);
		void AwakenWaitingFibers(Job *p_job);
	};
};
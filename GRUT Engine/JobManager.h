#pragma once
#include <windows.h>
#include <thread>
#include <vector>
#include <queue>
#include <optional>
#include "Singleton.h"
#include "Fiber.h"
#include "SpinLock.h"

constexpr unsigned FIBER_COUNT_PER_THREAD = 8;

namespace GRUT {
	class JobManager {
		friend class Singleton<JobManager>; 
	private:
		SpinLock m_fetchJobSpinLock;
		SpinLock m_launchThreadsSpinLock;
		std::vector<std::thread> m_threads;
		std::vector<std::unique_ptr<Fiber::Data>> m_fibers;
		std::queue<Job::Declaration> m_criticalPJobs;
		std::queue<Job::Declaration> m_highPJobs;
		std::queue<Job::Declaration> m_normalPJobs;
		std::queue<Job::Declaration> m_lowPJobs;
		JobManager();
		const void LaunchThreads();
		~JobManager();
	public:
		std::optional<Job::Declaration> FetchJob(Job::Priority p_priority = Job::Priority::LOW);
		void KickJob(Job::Declaration &&p_jobDecl);

		void KickJobs(int count, const Job::Declaration aDecl[]);
		void WaitForCounter(Job::Counter* pCounter);
		void KickJobAndWait(const Job::Declaration& decl);
		void KickJobsAndWait(int count, const Job::Declaration aDecl[]);
		Job::Counter* AllocCounter();
		void FreeCounter(Job::Counter* pCounter);
	};
};
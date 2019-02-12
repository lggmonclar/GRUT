#pragma once
#include "Job.h"
#include "Core/Parallelism/SpinLock.h"
#include <deque>
#include <queue>
#include <map>

namespace GRUT {

  constexpr unsigned FIBER_COUNT_PER_THREAD = 16;

  class JobManager {
  private:
    SpinLock m_fetchJobSpinLock;
    SpinLock m_fiberSwitchSpinLock;
    SpinLock m_threadsSpinLock;
    
    std::map<Job*, std::vector<Job*>> m_waitList;
    std::deque<void *> m_fibers;
    std::map<void *, Job*> m_fiberJobs;
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
    JobManager() = default;
    GRUT_API ~JobManager();
  public:
    JobManager(JobManager const &) = delete;
    JobManager& operator=(JobManager const &) = delete;
    GRUT_API static JobManager& Instance() {
      static JobManager instance{};
      return instance;
    }
    GRUT_API static void Initialize();
    GRUT_API static void ClearDoneJobs(std::vector<std::weak_ptr<Job>> &p_jobList);
    GRUT_API std::shared_ptr<Job> FetchJob(JobPriority p_priority = JobPriority::CRITICAL);
    GRUT_API std::weak_ptr<Job> KickJob(Job &&p_jobDecl, JobPriority p_priority = JobPriority::NORMAL);
    GRUT_API void WaitForJob(const std::weak_ptr<Job> &p_jobToWaitOnWeakPtr);
    GRUT_API void WaitForJobs(const std::vector<std::weak_ptr<Job>> &p_jobsToWaitOnWeakPtrs);
    GRUT_API void AwakenWaitingFibers(Job * const p_job);
  };
};
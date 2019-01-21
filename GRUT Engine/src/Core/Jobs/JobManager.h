#pragma once
#include "Job.h"
#include "Core/Parallelism/SpinLock.h"


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
    ~JobManager();
  public:
    JobManager(JobManager const &) = delete;
    JobManager& operator=(JobManager const &) = delete;
    static JobManager& Instance() {
      static JobManager instance{};
      return instance;
    }
    static void Initialize();
    std::shared_ptr<Job> FetchJob(JobPriority p_priority = JobPriority::LOW);
    std::weak_ptr<Job> KickJob(Job &&p_jobDecl);
    void WaitForJob(const std::weak_ptr<Job> &p_jobToWaitOnWeakPtr);
    void WaitForJobs(const std::vector<std::weak_ptr<Job>> &p_jobsToWaitOnWeakPtrs);
    void AwakenWaitingFibers(Job * const p_job);
  };
};
#include "grutpch.h"
#include "MemoryManager.h"
#include "Core/Parallelism/FrameParams.h"
#include "Core/Jobs/JobManager.h"

namespace GRUT {
  MemoryManager::~MemoryManager() {
  }

  void MemoryManager::Initialize() {
    MemoryManager::Instance();
  }
  void MemoryManager::Defragment(FrameParams& p_prevFrame, FrameParams& p_currFrame) {
    p_currFrame.memoryJob = JobManager::Instance().KickJob(Job([&]() {
      JobManager::Instance().WaitForJobs({ p_currFrame.renderJob, p_prevFrame.memoryJob });

      m_freeListAllocator.Defragment(1);

      p_currFrame.isDone = true;
    }));
  }
}
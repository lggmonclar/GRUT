#include "grutpch.h"
#include "MemoryManager.h"
#include "Core/Jobs/JobManager.h"

namespace GRUT {
  MemoryManager::~MemoryManager() {
  }

  void MemoryManager::Initialize() {
    MemoryManager::Instance();
  }
  void MemoryManager::Defragment(U8 p_blocksToShift) {
    //JobManager::Instance().KickJob(Job([&](std::shared_ptr<Job> p) {
      //m_freeListAllocator.Defragment(p_blocksToShift);
    //}));
  }
}
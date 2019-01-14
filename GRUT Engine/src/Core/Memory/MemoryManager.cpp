#include "grutpch.h"
#include "MemoryManager.h"

namespace GRUT {
  MemoryManager::~MemoryManager() {
  }

  void MemoryManager::Initialize() {
    MemoryManager::Instance();
  }
}
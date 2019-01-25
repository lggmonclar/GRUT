#pragma once
#include "Core/GRUTAlias.h"
#include "FreeListAllocator.h"

namespace GRUT {
  struct FrameParams;
  class MemoryManager {
  private:
    FreeListAllocator m_freeListAllocator{8_MB};
    MemoryManager() = default;
    ~MemoryManager() = default;
  public:
    static MemoryManager& Instance() {
      static MemoryManager instance{};
      return instance;
    }
    static void Initialize();
    template<class T, typename... Args>
    ObjectHandle<T> AllocOnFreeList(Args... args);
    template<class T>
    void FreeFromFreeList(T* p_obj);
    void Defragment(FrameParams& p_prevFrame, FrameParams& p_currFrame);
  };

  template<class T, typename... Args>
  inline ObjectHandle<T> MemoryManager::AllocOnFreeList(Args... args) {
    return m_freeListAllocator.Allocate<T>(args...);
  }
  template<class T>
  inline void MemoryManager::FreeFromFreeList(T* p_obj) {
    m_freeListAllocator.Free(p_obj);
  }
}
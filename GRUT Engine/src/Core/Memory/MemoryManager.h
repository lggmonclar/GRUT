#pragma once
#include "Core/GRUTAlias.h"
#include "FreeListAllocator.h"

namespace GRUT {
  class MemoryManager {
  private:
    FreeListAllocator m_freeListAllocator{8_MB};
    MemoryManager() = default;
    ~MemoryManager();
  public:
    static MemoryManager& Instance() {
      static MemoryManager instance{};
      return instance;
    }
    static void Initialize();
    template<class T> 
    ObjectHandle<T> AllocOnFreeList();
    template<class T>
    void FreeFromFreeList(T* p_obj);
    void Defragment(U8 p_blocksToShift);
  };

  template<class T>
  inline ObjectHandle<T> MemoryManager::AllocOnFreeList() {
    return m_freeListAllocator.Allocate<T>();
  }
  template<class T>
  inline void MemoryManager::FreeFromFreeList(T* p_obj) {
    m_freeListAllocator.Free(p_obj);
  }
}
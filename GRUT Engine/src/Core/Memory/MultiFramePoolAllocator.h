#pragma once
#include "Core/GRUTAlias.h"

namespace GRUT {
  class MultiFramePoolAllocator {
  private:
    void* m_memoryHead;
    const U8 m_frames;
    const U16 m_slots;
    const Size m_slotSize;
    void ResetPool(const U8 p_frame);
  public:
    MultiFramePoolAllocator(const Size p_totalSize, const U8 p_frames, const U16 p_slots);
    ~MultiFramePoolAllocator();
    template<class T>
    T GetObject(U16 index);
  };
}
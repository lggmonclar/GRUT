#include "grutpch.h"
#include "MultiFramePoolAllocator.h"

namespace GRUT {
  void MultiFramePoolAllocator::ResetPool(const U8 p_frame)
  {
  }
  MultiFramePoolAllocator::MultiFramePoolAllocator(const Size p_totalSize, const U8 p_frames, const U16 p_slots) :
    m_slotSize(p_totalSize/p_frames/p_slots), m_frames(p_frames), m_slots(p_slots) {
    m_memoryHead = malloc(p_totalSize);
  }

  MultiFramePoolAllocator::~MultiFramePoolAllocator() {
    free(m_memoryHead);
  }
}

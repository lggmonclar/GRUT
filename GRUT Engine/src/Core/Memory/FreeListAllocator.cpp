#include "grutpch.h"                     
#include "FreeListAllocator.h"

namespace GRUT { 
  FreeListAllocator::FreeListAllocator(const Size p_size) {
    m_memoryHead = malloc(p_size);
    m_headNode = new (m_memoryHead)Node(p_size);
  }
  void FreeListAllocator::Free(void * p_obj) {
    Node* nextNode = reinterpret_cast<Node*>(reinterpret_cast<U8*>(p_obj) - sizeof(AllocHeader));
    nextNode->next = nullptr;

    Node* prevNode = m_headNode;
    if (nextNode < prevNode) {
      m_headNode = nextNode;
      nextNode = prevNode;
    }
    for (prevNode = m_headNode; (prevNode->next < nextNode && prevNode->next != nullptr); prevNode = prevNode->next);
    
    //Coalesce forward
    if (reinterpret_cast<Node*>(reinterpret_cast<U8*>(nextNode) + nextNode->size) == prevNode->next) {
      nextNode->size += prevNode->next->size;
    }
    else {
      nextNode->next = prevNode->next;
    }
    //Coalesce behind
    if (reinterpret_cast<Node*>(reinterpret_cast<U8*>(prevNode) + prevNode->size) == nextNode) {
      prevNode->size += nextNode->size;
    }
    else {
      prevNode->next = nextNode;
    }
  }

  void FreeListAllocator::Defragment(U8 p_blocksToShift) {
  }

  FreeListAllocator::~FreeListAllocator() {
    free(m_memoryHead);
  }
}
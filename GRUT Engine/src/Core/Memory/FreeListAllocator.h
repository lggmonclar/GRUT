#pragma once
#include "Core/GRUTAlias.h"
#include "ObjectHandle.h"

namespace GRUT { 
  constexpr U16 AVAILABLE_HANDLES = 2048;
  class FreeListAllocator {
  private:
    struct Node {
      Size size;
      Node* next;
      Node(const Size size) : size(size), next(nullptr) {}
    };    
    struct AllocHeader {
      Size size;
      AllocHeader(const Size size) : size(size) {}
    };
    void* m_memoryHead;
    Node *m_headNode; 
    HandleEntry m_handles[AVAILABLE_HANDLES];
  public:
    FreeListAllocator(const Size p_size);
    template<class T>
    ObjectHandle<T> Allocate();
    void Free(void* p_obj);
    void Defragment(U8 p_blocksToShift);
    ~FreeListAllocator();
  };
  template<class T>
  inline ObjectHandle<T> FreeListAllocator::Allocate() {
    Node* prevNode = nullptr;
    Node* firstFitNode = m_headNode;
    Size allocSize = sizeof(T) + sizeof(AllocHeader);
    while (firstFitNode->size < allocSize) {
      prevNode = firstFitNode;
      firstFitNode = firstFitNode->next;
    }
    Node* shiftedNode = firstFitNode;
    shiftedNode = reinterpret_cast<Node*>(reinterpret_cast<U8*>(shiftedNode) + allocSize);
    shiftedNode->size = firstFitNode->size - allocSize;
    shiftedNode->next = firstFitNode->next;
    if (prevNode != nullptr) {
      prevNode->next = firstFitNode;
    }
    if (m_headNode == firstFitNode) {
      m_headNode = shiftedNode;
    }

    firstFitNode->size = sizeof(T) + sizeof(AllocHeader);
    T* newObj = new (reinterpret_cast<U8*>(firstFitNode) + sizeof(AllocHeader)) T;
    
    U32 i = 0;
    for (; i < AVAILABLE_HANDLES; i++) {
      if (m_handles[i].m_isAvailable) {
        m_handles[i] = { 0, static_cast<void*>(newObj), false };
        break;
      }
    }

    return ObjectHandle<T>(i, m_handles);
  }
}
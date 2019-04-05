#include "grutpch.h"                     
#include "FreeListAllocator.h"

namespace GRUT { 
  FreeListAllocator::FreeListAllocator(const Size p_size) {
    m_memoryHead = malloc(p_size);
    m_headNode = new (m_memoryHead)Node(p_size);
  }
  void FreeListAllocator::Free(void * p_obj) {
    m_lock.Acquire();

    AllocHeader* occupiedBlock = reinterpret_cast<AllocHeader*>(reinterpret_cast<U8*>(p_obj) - sizeof(AllocHeader));
    m_handles[occupiedBlock->handleIdx].m_isAvailable = true;

    Node* newNode = reinterpret_cast<Node*>(occupiedBlock);
    newNode->next = nullptr;

    Node* currPrevNode = m_headNode;
    if (newNode < currPrevNode) {
      m_headNode = newNode;
      newNode = currPrevNode;
    }
    for (currPrevNode = m_headNode; (currPrevNode->next < newNode && currPrevNode->next != nullptr); currPrevNode = currPrevNode->next);

    //Try to coalesce the new node with the next free node
    if (!Coalesce(newNode, currPrevNode->next) && currPrevNode->next != nullptr)
      newNode->next = currPrevNode->next;
    //and then the previous node
    if (!Coalesce(currPrevNode, newNode))
      currPrevNode->next = newNode;
    else
      currPrevNode->next = newNode->next;

    m_lock.Release();
  }

  void FreeListAllocator::Defragment(U8 p_blocksToShift) {
    m_lock.Acquire();
    U8 blocksShifted = 0;

    Node* node = m_headNode;
    while (node != nullptr && node->next != nullptr && blocksShifted < p_blocksToShift) {
      if (!Coalesce(node, node->next)) {
        //Can be defragmented
        Node cpy = *node;

        AllocHeader* occupiedBlock = reinterpret_cast<AllocHeader*>(reinterpret_cast<U8*>(node) + node->size);
        m_handles[occupiedBlock->handleIdx].m_ptr = reinterpret_cast<U8*>(node) + sizeof(AllocHeader);
        
        memmove(node, occupiedBlock, occupiedBlock->size);

        if (m_headNode == node) {
          m_headNode = reinterpret_cast<Node*>(reinterpret_cast<U8*>(m_headNode) + occupiedBlock->size );
        }
        node = reinterpret_cast<Node*>(reinterpret_cast<U8*>(node) + occupiedBlock->size);
        *node = cpy;

        blocksShifted++;
      }
      else {
        node->next = node->next->next;
        node = node->next;
      }
    }
    m_lock.Release();
  }

  bool FreeListAllocator::Coalesce(Node* p_backNode, Node* p_frontNode) {
    if (reinterpret_cast<Node*>(reinterpret_cast<U8*>(p_backNode) + p_backNode->size) == p_frontNode) {
      p_backNode->size += p_frontNode->size;
      return true;
    }
    return false;
  }

  FreeListAllocator::~FreeListAllocator() {
    free(m_memoryHead);
  }
}
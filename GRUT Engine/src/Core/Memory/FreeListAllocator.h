#pragma once
#include "Core/GRUTAlias.h"
#include "ObjectHandle.h"
#include "Core/Parallelism/SpinLock.h"
#include "Core/Debugging/Logger.h"

namespace GRUT {
    constexpr U16 AVAILABLE_HANDLES = 16384;
    class FreeListAllocator {
        private:
            SpinLock m_lock;
            struct Node {
                Size size;
                Node* next;
                Node(const Size size) : size(size), next(nullptr) {}
            };
            struct AllocHeader {
                Size size;
                U32  handleIdx = 0;
                AllocHeader(const Size size) : size(size) {}
            };
            void* m_memoryHead;
            Node* m_headNode;
            HandleEntry m_handles[AVAILABLE_HANDLES];

        public:
            FreeListAllocator(const Size p_size);
            template<class T, typename... Args>
            ObjectHandle<T> Allocate(Args... args);
            void Free(void* p_obj);
            void Defragment(U8 p_blocksToShift);
            bool Coalesce(Node* p_backNode, Node* p_frontNode);
            ~FreeListAllocator();
    };

    template<class T, typename... Args>
    inline ObjectHandle<T> FreeListAllocator::Allocate(Args... args) {
        m_lock.Acquire();
        Node* prevNode = nullptr;
        Node* firstFitNode = m_headNode;
        Size allocSize = sizeof(T) + sizeof(AllocHeader);
        while (firstFitNode->size < allocSize) {
            prevNode = firstFitNode;
            firstFitNode = firstFitNode->next;
        }

        if (prevNode != nullptr) {
            prevNode->next = firstFitNode;
        }

        if (firstFitNode->size - allocSize > 0) {
            Node* shiftedNode = firstFitNode;
            shiftedNode = reinterpret_cast<Node*>(reinterpret_cast<U8*>(shiftedNode) + allocSize);
            shiftedNode->size = firstFitNode->size - allocSize;
            shiftedNode->next = firstFitNode->next;
            if (m_headNode == firstFitNode) {
                m_headNode = shiftedNode;
            }
        }
        else if (m_headNode == firstFitNode) {
            m_headNode = m_headNode->next;
        }

        AllocHeader* objHeader = reinterpret_cast<AllocHeader*>(firstFitNode);

        T* newObj = new (reinterpret_cast<U8*>(objHeader) + sizeof(AllocHeader)) T(args...);

        U32 i = 0;
        bool availableHandleFound = false;
        for (; i < AVAILABLE_HANDLES; i++) {
            if (m_handles[i].m_isAvailable) {
                availableHandleFound = true;
                m_handles[i] = { static_cast<void*>(newObj), false };
                break;
            }
        }

        if (!availableHandleFound) {
            LOG_ERROR("Too many object handles created. New handle allocation cannot complete.");
        }

        objHeader->size = sizeof(T) + sizeof(AllocHeader);
        objHeader->handleIdx = i;

        m_lock.Release();
        return ObjectHandle<T>([&, i]() {
            m_lock.Acquire();
            HandleEntry entry = m_handles[i];
            m_lock.Release();
            return entry;
        });
    }
}
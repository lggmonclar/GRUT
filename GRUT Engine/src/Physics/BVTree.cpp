#include "grutpch.h"
#include "BVTree.h"
#include "Core/Memory/MemoryManager.h"
#include "Core/Debugging/Box.h"

namespace GRUT {
    BVTree::Node::Node(ObjectHandle<ICollider> const p_collider) :
        m_collider(p_collider), m_aabb(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f)) {
        JobManager::Instance().KickJob([=, &m_aabb = m_aabb] {
            m_aabb = p_collider->GetFatAABB();
                                       });
    }

    void BVTree::Node::UpdateBranchAABB() {
        m_aabb = AABB::Encapsulate(m_left->m_aabb, m_right->m_aabb);
    }

    void BVTree::Node::UpdateLeafAABB() {
        m_aabb = m_collider->GetFatAABB();
    }

    void BVTree::Node::SwapOutChild(ObjectHandle<Node> p_oldChild, ObjectHandle<Node> p_newChild) {
        if (p_oldChild == m_left) {
            m_left = p_newChild;
            m_left->m_parent = m_handle;
        }
        else {
            m_right = p_newChild;
            m_right->m_parent = m_handle;
        }
    }

    bool BVTree::Node::IsLeaf() const {
        return &m_left == nullptr;
    }

    bool BVTree::Node::IsInFatAABB() const {
        return m_aabb.Contains(m_collider->GetAABB());
    }

    void BVTree::AddNode(ObjectHandle<Node> p_newNode) {
        AABB newAABB = p_newNode->m_aabb;

        if (&m_root == nullptr) {
            m_root = p_newNode;
            m_root->m_parent.Clear();
        }
        else {
            ObjectHandle<Node> curr = m_root;

            while (!curr->IsLeaf()) {
                float leftIncrease =
                    AABB::Encapsulate(curr->m_left->m_aabb, newAABB).SurfaceArea() -
                    curr->m_left->m_aabb.SurfaceArea();

                float rightIncrease =
                    AABB::Encapsulate(curr->m_right->m_aabb, newAABB).SurfaceArea() -
                    curr->m_right->m_aabb.SurfaceArea();

                if (leftIncrease > rightIncrease) {
                    curr = curr->m_right;
                }
                else {
                    curr = curr->m_left;
                }
            }

            if (curr == m_root) {
                m_root = MemoryManager::Instance().AllocOnFreeList<Node>(AABB::Encapsulate(curr->m_aabb, newAABB));
                m_root->m_handle = m_root;
                curr->m_parent = m_root;
                p_newNode->m_parent = m_root;
                m_root->m_left = curr;
                m_root->m_right = p_newNode;
            }
            else {
                ObjectHandle<Node> newBranch = MemoryManager::Instance().AllocOnFreeList<Node>(AABB::Encapsulate(curr->m_aabb, p_newNode->m_aabb));
                newBranch->m_handle = newBranch;
                newBranch->m_parent = curr->m_parent;
                curr->m_parent->SwapOutChild(curr, newBranch);
                curr->m_parent = newBranch;
                p_newNode->m_parent = newBranch;
                newBranch->m_left = curr;
                newBranch->m_right = p_newNode;

                ObjectHandle<Node> parent = newBranch->m_parent;
                while (&parent != nullptr) {
                    parent->UpdateBranchAABB();
                    parent = parent->m_parent;
                }
            }
        }
    }

    void BVTree::RemoveNode(ObjectHandle<Node> p_node, bool p_deleteNode) {
        if (p_node == m_root) {
            m_root.Clear();
        }
        else if (p_node->m_parent == m_root) {
            ObjectHandle<Node> newRoot;

            if (p_node == m_root->m_left) {
                newRoot = m_root->m_right;
            }
            else {
                newRoot = m_root->m_left;
            }

            MemoryManager::Instance().FreeFromFreeList<Node>(&m_root);
            m_root = newRoot;
            m_root->m_parent.Clear();
        }
        else {
            ObjectHandle<Node> parent = p_node->m_parent;
            ObjectHandle<Node> grandParent = parent->m_parent;

            if (p_node == parent->m_left) {
                grandParent->SwapOutChild(parent, parent->m_right);
            }
            else {
                grandParent->SwapOutChild(parent, parent->m_left);
            }

            MemoryManager::Instance().FreeFromFreeList<Node>(&parent);

            ObjectHandle<Node> curr = grandParent;
            while (&curr != nullptr) {
                curr->UpdateBranchAABB();
                curr = curr->m_parent;
            }
        }

        if (p_deleteNode) {
            MemoryManager::Instance().FreeFromFreeList<Node>(&p_node);
        }
    }

    void BVTree::AddCollider(ObjectHandle<ICollider> p_collider) {
        ObjectHandle<Node> newNode = MemoryManager::Instance().AllocOnFreeList<Node>(p_collider);
        newNode->m_handle = newNode;
        m_colNodeMap.insert({ p_collider, newNode });
        AddNode(newNode);
    }
    void BVTree::RemoveCollider(ObjectHandle<ICollider> p_collider) {
        auto it = m_colNodeMap.find(p_collider);
        RemoveNode(it->second, true);
        m_colNodeMap.erase(it);
    }

    void BVTree::Update() {
        std::vector<ObjectHandle<Node>> toReInsert;

        std::queue<ObjectHandle<Node>> q;
        if (&m_root != nullptr) {
            q.push(m_root);
        }

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            if (&curr->m_left != nullptr) {
                q.push(curr->m_left);
            }
            if (&curr->m_right != nullptr) {
                q.push(curr->m_right);
            }

            if (curr->IsLeaf() && !curr->IsInFatAABB()) {
                auto parent = curr->m_parent;
                toReInsert.push_back(curr);
            }
        }

        for (auto node : toReInsert) {
            RemoveNode(node, false);
        }

        for (auto node : toReInsert) {
            node->UpdateLeafAABB();
            AddNode(node);
        }

        //DebugDraw();
    }

    const ColliderPairSet BVTree::GetCollisionPairs() {
        ColliderPairSet colliderPairSet;

        for (const auto& pair : m_colNodeMap) {
            auto currCollider = pair.first;
            AABB aabb = currCollider->GetFatAABB();
            std::queue<ObjectHandle<Node>> q;

            if (&m_root != nullptr) {
                q.push(m_root);
            }

            while (!q.empty()) {
                auto currNode = q.front();
                q.pop();

                if (currNode->IsLeaf()) {
                    if (&currCollider != &currNode->m_collider) {
                        colliderPairSet.insert({ currCollider, currNode->m_collider });
                    }
                }
                else {
                    if (currNode->m_left->m_aabb.Intersects(aabb)) {
                        q.push(currNode->m_left);
                    }
                    if (currNode->m_right->m_aabb.Intersects(aabb)) {
                        q.push(currNode->m_right);
                    }
                }
            }
        }

        return colliderPairSet;
    }

    void BVTree::DebugDraw() const {
        std::queue<ObjectHandle<Node>> q;

        if (&m_root != nullptr) {
            q.push(m_root);
        }

        while (!q.empty()) {
            ObjectHandle<Node> curr = q.front();

            if (curr->IsLeaf()) {
                auto aabb = curr->m_aabb;
                DEBUG_DRAW_BOX(curr->m_aabb.GetCenter(), curr->m_aabb.GetSize(), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.95f, 1.0f), true);
            }
            else {
                int depth = 0;
                auto parent = curr->m_parent;
                while (&parent != nullptr) {
                    ++depth;
                    parent = parent->m_parent;
                }

                DEBUG_DRAW_BOX(curr->m_aabb.GetCenter(), curr->m_aabb.GetSize(), Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 0.95f, 0.2f), true);
            }

            q.pop();
            if (&curr->m_left != nullptr) {
                q.push(curr->m_left);
            }
            if (&curr->m_right != nullptr) {
                q.push(curr->m_right);
            }

        }
    }
}

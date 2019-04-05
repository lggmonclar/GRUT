#pragma once
#include <GRUTMath.h>
#include "AABB.h"
#include "Scene/Components/Physics/Collider.h"
#include "CollisionUtil.h"

using namespace GRUT::Math;
namespace GRUT {
  class BVTree {
  private:
    struct Node {
      Node(AABB aabb) : m_aabb(std::move(aabb)) {}
      Node(ObjectHandle<Collider> const p_collider);

      void UpdateBranchAABB();
      void UpdateLeafAABB();
      void SwapOutChild(ObjectHandle<Node> p_oldChild, ObjectHandle<Node> p_newChild);

      bool IsLeaf() const;
      bool IsInFatAABB() const;

      ObjectHandle<Collider> m_collider;
      AABB m_aabb;

      ObjectHandle<Node> m_handle;
      ObjectHandle<Node> m_parent;
      ObjectHandle<Node> m_left;
      ObjectHandle<Node> m_right;
    };
    ObjectHandle<Node> m_root;
    std::map<ObjectHandle<Collider>, ObjectHandle<Node>> m_colNodeMap;
    void AddNode(ObjectHandle<Node> newNode);
    void RemoveNode(ObjectHandle<Node> node, bool deleteNode);
    void DebugDraw() const;
  public:
    BVTree() = default;
    void AddCollider(ObjectHandle<Collider> p_collider);
    void RemoveCollider(ObjectHandle<Collider> p_collider);
    void Update();
    const ColliderPairSet GetCollisionPairs();
  };
}
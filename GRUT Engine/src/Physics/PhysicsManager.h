#pragma once
#include "DLLMacros.h"
#include "BVTree.h"

namespace GRUT {
  struct FrameParams;
  template<class C>
  class ObjectHandle;
  class Collider;
  struct Job;

  class PhysicsManager {
  private:
    BVTree m_BVTree;
    ColliderPairSet m_activeCollisions;
    std::vector<ObjectHandle<Collider>> m_registeredColliders;
    void CheckCollisions();
  public:
    GRUT_API static PhysicsManager& Instance() {
      static PhysicsManager instance{};
      return instance;
    }
    static void Initialize();
    void Update(FrameParams& p_prevFrame, FrameParams& p_currFrame);
    GRUT_API void RegisterCollider(const ObjectHandle<Collider> &p_collider);
    GRUT_API void RemoveCollider(const ObjectHandle<Collider>& p_collider);
  };
}
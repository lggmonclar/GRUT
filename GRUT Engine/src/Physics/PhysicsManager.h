#pragma once
#include "DLLMacros.h"

namespace GRUT {
  struct FrameParams;
  template<class C>
  class ObjectHandle;
  class Collider;

  class PhysicsManager {
  private:
    std::map<ObjectHandle<Collider>, std::vector<ObjectHandle<Collider>>> m_activeCollisions;
    std::vector<ObjectHandle<Collider>> m_registeredColliders;
    void CheckCollisions();
  public:
    GRUT_API static PhysicsManager& Instance() {
      static PhysicsManager instance{};
      return instance;
    }
    static void Initialize();
    void Update(FrameParams& p_prevFrame, FrameParams& p_currFrame);
    GRUT_API std::vector<ObjectHandle<Collider>>::iterator RegisterCollider(const ObjectHandle<Collider> &p_collider);
    GRUT_API void RemoveCollider(std::vector<ObjectHandle<Collider>>::iterator p_iterator);
  };
}
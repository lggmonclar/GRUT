#pragma once
#include "ICollider.h"

namespace GRUT {
  class BoxCollider : public ICollider {
  private:
    Vector3 m_vertices[8]{
      Vector3(0.0f, 1.0f, 0.0f), //Front top m_left
      Vector3(1.0f, 1.0f, 0.0f), //Front top m_right
      Vector3(0.0f, 0.0f, 0.0f), //Front bottom m_left
      Vector3(1.0f, 0.0f, 0.0f), //Front bottom m_right
      Vector3(0.0f, 1.0f, 1.0f), //Back top m_left
      Vector3(1.0f, 1.0f, 1.0f), //Back top m_right
      Vector3(0.0f, 0.0f, 1.0f), //Back bottom m_left
      Vector3(1.0f, 0.0f, 1.0f)  //Back bottom m_right
    };
    Vector3 m_colliderColor = Vector3(0.0f, 0.95f, 0.2f);
  public:
    Vector3 Support(const Vector3 &p_direction) override;
    void Update(float p_deltaTime) override;
    void OnCollisionEnter(ObjectHandle<ICollider> &p_other) override;
    void OnCollisionExit(ObjectHandle<ICollider> &p_other) override;
    class AABB GetFatAABB() override;
    class AABB GetAABB() override;
  };
}
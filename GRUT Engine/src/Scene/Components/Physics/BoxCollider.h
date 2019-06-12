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
    GRUT_API Vector3 Support(const Vector3 &p_direction) override;
    GRUT_API void Update(float p_deltaTime) override;
    GRUT_API void OnCollisionEnter(ObjectHandle<ICollider> &p_other) override;
    GRUT_API void OnCollisionExit(ObjectHandle<ICollider> &p_other) override;
    GRUT_API class AABB GetFatAABB() override;
    GRUT_API class AABB GetAABB() override;
  };
}
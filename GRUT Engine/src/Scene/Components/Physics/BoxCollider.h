#pragma once
#include "Collider.h"

namespace GRUT {
  class BoxCollider : public Collider {
  private:
    Vector<3> m_vertices[8]{
      Vector<3>(0.0f, 1.0f, 0.0f), //Front top left
      Vector<3>(1.0f, 1.0f, 0.0f), //Front top right
      Vector<3>(0.0f, 0.0f, 0.0f), //Front bottom left
      Vector<3>(1.0f, 0.0f, 0.0f), //Front bottom right
      Vector<3>(0.0f, 1.0f, 1.0f), //Back top left
      Vector<3>(1.0f, 1.0f, 1.0f), //Back top right
      Vector<3>(0.0f, 0.0f, 1.0f), //Back bottom left
      Vector<3>(1.0f, 0.0f, 1.0f)  //Back bottom right
    };
  public:
    GRUT_API Vector<3> Support(const Vector<3> &p_direction) override;
    GRUT_API void Update(float p_deltaTime) override;
  };
}
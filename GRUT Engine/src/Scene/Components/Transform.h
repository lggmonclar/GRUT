#pragma once
#include "Component.h"
#include <GRUTMath.h>

namespace GRUT {
  using namespace GRUT::Math;
  class Transform : public Component {
  private:
  public:
    Matrix<4> modelMatrix;
    Vector<3> GetPosition();
    void Translate(const Vector<3>& p_vec);
    void Rotate(const Vector<3>& p_rotations);
    void RotateAbout(const Vector<3>& p_axis, const float p_val);
    void LookAt(const Vector<3>& p_target);
    void SetScale(const Vector<3>& p_scale);
  };
}
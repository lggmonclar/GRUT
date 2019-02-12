#pragma once
#include "Component.h"
#include <GRUTMath.h>

namespace GRUT {
  using namespace GRUT::Math;
  class Transform : public Component {
  private:
  public:
    Matrix<4> modelMatrix;
    GRUT_API Vector<3> GetPosition();
    GRUT_API void Translate(const Vector<3>& p_vec);
    GRUT_API void Rotate(const Vector<3>& p_rotations);
    GRUT_API void RotateAbout(const Vector<3>& p_axis, const float p_val);
    GRUT_API void LookAt(const Vector<3>& p_target);
    GRUT_API void SetScale(const Vector<3>& p_scale);
  };
}
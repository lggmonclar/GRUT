#pragma once
#include "Component.h"
#include <GRUTMath.h>

namespace GRUT {
  using namespace GRUT::Math;
  enum class Space {
    SELF,
    WORLD
  };
  class Transform : public Component {
  private:
    Vector<3> m_localScale{ 1.0f, 1.0f, 1.0f };
  public:
    bool isDirty = false;
    Matrix<4> modelMatrix;
    GRUT_API Vector<3> GetPosition();
    GRUT_API Vector<3> GetRotation();
    GRUT_API Vector<3> GetScale();
    GRUT_API Vector<3> GetRightVector();
    GRUT_API Vector<3> GetUpVector();
    GRUT_API Vector<3> GetFrontVector();
    GRUT_API void SetPosition(const Vector<3>& p_vec);
    GRUT_API void Translate(const Vector<3>& p_vec);
    GRUT_API void Rotate(const Vector<3>& p_rotations, const Space p_space = Space::SELF);
    GRUT_API void RotateAbout(const Vector<3>& p_axis, const float p_val);
    GRUT_API void SetRotation(const Vector<3> &p_rotation);
    GRUT_API void LookAt(const Vector<3>& p_target);
    GRUT_API void SetScale(const Vector<3>& p_scale);
    void Update(float p_deltaTime) override;
  };
}
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
    Vector3 m_localScale{ 1.0f, 1.0f, 1.0f };
  public:
    bool isDirty = false;
    Matrix4 modelMatrix;
    Vector3 GetPosition();
    Vector3 GetRotation();
    Vector3 GetScale();
    Vector3 GetRightVector();
    Vector3 GetUpVector();
    Vector3 GetFrontVector();
    void SetPosition(const Vector3& p_vec);
    void Translate(const Vector3& p_vec);
    void Rotate(const Vector3& p_rotations, const Space p_space = Space::SELF);
    void RotateAbout(const Vector3& p_axis, const float p_val);
    void SetRotation(const Vector3 &p_rotation);
    void LookAt(const Vector3& p_target);
    void SetScale(const Vector3& p_scale);
    void Update(float p_deltaTime) override;
  };
}
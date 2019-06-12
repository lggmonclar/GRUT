#include "grutpch.h"
#include "Transform.h"

namespace GRUT {
  Vector3 Transform::GetPosition() {
    auto &tRow = modelMatrix[3];
    return Vector3(tRow.x, tRow.y, tRow.z);
  }
  Vector3 Transform::GetRightVector() {
    auto &xRow = modelMatrix[0];
    return -Vector3(xRow.x, xRow.y, xRow.z).Normalized();
  }
  Vector3 Transform::GetUpVector() {
    auto &yRow = modelMatrix[1];
    return Vector3(yRow.x, yRow.y, yRow.z).Normalized();
  }
  Vector3 Transform::GetFrontVector() {
    auto &zRow = modelMatrix[2];
    return Vector3(zRow.x, zRow.y, zRow.z).Normalized();
  }
  void Transform::Translate(const Vector3& p_vec) {
    modelMatrix.Translate(p_vec);
    isDirty = true;
  }
  void Transform::Rotate(const Vector3& p_rotations, const Space p_space) {
    auto pos = GetPosition();
    if(p_space == Space::SELF)
      Translate(-pos);
    modelMatrix.RotateZ(p_rotations.z);
    modelMatrix.RotateX(p_rotations.x);
    modelMatrix.RotateY(p_rotations.y);
    if (p_space == Space::SELF)
      Translate(pos);
    isDirty = true;
  }
  void Transform::RotateAbout(const Vector3& p_axis, const float p_val) {
    modelMatrix.RotateAbout(p_axis, p_val);
    isDirty = true;
  }
  Vector3 Transform::GetRotation() {
    return modelMatrix.GetRotation();
  }
  Vector3 Transform::GetScale() {
    return m_localScale;
  }
  void Transform::SetRotation(const Vector3 &p_rotation) {
    modelMatrix.SetRotation(p_rotation);
    isDirty = true;
  }

  void Transform::SetPosition(const Vector3 &p_vec) {
    modelMatrix.SetPosition(p_vec);
    isDirty = true;
  }

  void Transform::LookAt(const Vector3& p_target) {
    auto pos = GetPosition();
    modelMatrix.LookAt(pos, pos + p_target, Vector3(0.0f, 1.0f, 0.0f));
    isDirty = true;
  }
  void Transform::SetScale(const Vector3& p_scale) {
    m_localScale = p_scale;
    modelMatrix.Scale(p_scale);
    isDirty = true;
  }

  void Transform::Update(float p_deltaTime) {
    isDirty = false;
  }

}

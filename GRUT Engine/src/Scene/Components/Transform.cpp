#include "grutpch.h"
#include "Transform.h"

namespace GRUT {
  Vector<3> Transform::GetPosition() {
    auto &tRow = modelMatrix[3];
    return Vector<3>(tRow.x(), tRow.y(), tRow.z());
  }
  void Transform::Translate(const Vector<3>& p_vec) {
    modelMatrix.Translate(p_vec);
  }
  void Transform::Rotate(const Vector<3>& p_rotations) {
    modelMatrix.RotateZ(p_rotations.z());
    modelMatrix.RotateX(p_rotations.x());
    modelMatrix.RotateY(p_rotations.y());
  }
  void Transform::RotateAbout(const Vector<3>& p_axis, const float p_val) {
    modelMatrix.RotateAbout(p_axis, p_val);
  }
  void Transform::LookAt(const Vector<3>& p_target) {
    auto pos = GetPosition();
    modelMatrix.LookAt(pos, pos + p_target, Vector<3>(0.0f, 1.0f, 0.0f));
  }
  void Transform::SetScale(const Vector<3>& p_scale) {
    modelMatrix.Scale(p_scale);
  }
}

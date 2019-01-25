#include "grutpch.h"
#include "Camera.h"

namespace GRUT {
  void Camera::UpdateCameraVectors() {
    Math::Vector<3> newFront;
    newFront[0] = static_cast<float>(cos(Math::deg2rad(m_yaw)) * cos(Math::deg2rad(m_pitch)));
    newFront[1] = static_cast<float>(sin(Math::deg2rad(m_pitch)));
    newFront[2] = static_cast<float>(sin(Math::deg2rad(m_yaw)) * cos(Math::deg2rad(m_pitch)));
    front = newFront.Normalized();
    right = front.Cross(worldUp).Normalized();
    up = right.Cross(front).Normalized();
  }
  Camera::Camera(Math::Vector<3> pUp, float pYaw, float pPitch) : worldUp(pUp), m_yaw(pYaw), m_pitch(pPitch), front(Math::Vector<3>(0.0f, 0.0f, -1.0f)) {
    UpdateCameraVectors();
  }

  Camera::Camera(float upX, float upY, float upZ, float pYaw, float pPitch) :
    worldUp(Math::Vector<3>(upX, upY, upZ)), m_yaw(pYaw), m_pitch(pPitch),
    front(Math::Vector<3>(0.0f, 0.0f, -1.0f)) {
    UpdateCameraVectors();
  }

  void Camera::UpdateProjectionMatrix() {
    if (m_isOrthographic) {
      m_projectionMatrix = Math::Matrix<4>::OrthographicProjection(m_orthoLeft, m_orthoRight, m_orthoBottom, m_orthoTop, m_nearPlane, m_farPlane);
    }
    else {
      //TODO: take resolution into account
      m_projectionMatrix = Math::Matrix<4>::PerspectiveProjection(static_cast<float>(Math::deg2rad(m_fov)), (float)800 / (float)600, m_nearPlane, m_farPlane);
    }
  }

  void Camera::SetOrtographic(bool p_val) {
    m_isOrthographic = true;
    m_isDirty = true;
  }

  void Camera::SetOrthoLeft(float p_val) {
    m_orthoLeft = p_val;
    m_isDirty = true;
  }
  void Camera::SetOrthoRight(float p_val) {
    m_orthoRight = p_val;
    m_isDirty = true;
  }
  void Camera::SetOrthoTop(float p_val) {
    m_orthoTop = p_val;
    m_isDirty = true;
  }
  void Camera::SetOrthoBottom(float p_val) {
    m_orthoBottom = p_val;
    m_isDirty = true;
  }

  void Camera::SetNearPlane(float p_val) {
    m_nearPlane = p_val;
    m_isDirty = true;
  }

  void Camera::SetFarPlane(float p_val) {
    m_farPlane = p_val;
    m_isDirty = true;
  }

  void Camera::SetFieldOfView(float p_val) {
    m_fov = p_val;
    m_isDirty = true;
  }

  void Camera::SetYaw(float y) {
    m_yaw = y;
    m_isDirty = true;
  }

  void Camera::SetPitch(float p) {
    m_pitch = p;
    m_isDirty = true;
  }

  Math::Matrix<4>& Camera::GetViewMatrix() {
    auto pos = gameObject->transform->GetPosition();
    return view.LookAt(pos, pos + front, up);
  }

  Math::Matrix<4>& Camera::GetProjectionMatrix() {
    return m_projectionMatrix;
  }

  void Camera::Update(float p_deltaTime) {
    if (m_isDirty) {
      UpdateProjectionMatrix();
      UpdateCameraVectors();
    }
  }
}
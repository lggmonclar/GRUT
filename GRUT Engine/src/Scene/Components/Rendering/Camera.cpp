#include "grutpch.h"
#include "Camera.h"
#include "Graphics/RenderManager.h"
#include "Graphics/Shaders/GLShader.h"
#include "Core/Config/Config.h"

namespace GRUT {
  void Camera::Initialize() {
    m_isDirty = true;
    UpdateProjectionMatrix();
  }

  void Camera::UpdateProjectionMatrix() {
    if (m_isOrthographic) {
      m_projectionMatrix = Math::Matrix4::OrthographicProjection(m_orthoLeft, m_orthoRight, m_orthoBottom, m_orthoTop, m_nearPlane, m_farPlane);
    }
    else {
      auto width = GET_CVAR(CVarInt, "window_width");
      auto height = GET_CVAR(CVarInt, "window_height");
      m_projectionMatrix = Math::Matrix4::PerspectiveProjection(static_cast<float>(Math::deg2rad(m_fov)), (float)width / (float)height, m_nearPlane, m_farPlane);
    }
  }

  void Camera::SetOrtographic(bool p_val) {
    if (m_isOrthographic != p_val) {
      m_isOrthographic = p_val;
      m_isDirty = true;
    }
  }

  void Camera::SetOrthoLeft(float p_val) {
    if (m_orthoLeft != p_val) {
      m_orthoLeft = p_val;
      m_isDirty = true;
    }
  }
  void Camera::SetOrthoRight(float p_val) {
    if (m_orthoRight != p_val) {
      m_orthoRight = p_val;
      m_isDirty = true;
    }
  }
  void Camera::SetOrthoTop(float p_val) {
    if (m_orthoTop != p_val) {
      m_orthoTop = p_val;
      m_isDirty = true;
    }
  }
  void Camera::SetOrthoBottom(float p_val) {
    if (m_orthoBottom != p_val) {
      m_orthoBottom = p_val;
      m_isDirty = true;
    }
  }

  void Camera::SetNearPlane(float p_val) {
    if (m_nearPlane != p_val) {
      m_nearPlane = p_val;
      m_isDirty = true;
    }
  }

  void Camera::SetFarPlane(float p_val) {
    if (m_farPlane != p_val) {
      m_farPlane = p_val;
      m_isDirty = true;
    }
  }

  void Camera::SetFieldOfView(float p_val) {
    if (m_fov != p_val) {
      m_fov = p_val;
      m_isDirty = true;
    }
  }

  Math::Matrix4 Camera::GetViewMatrix() {
    auto transform = gameObject->transform;
    auto front = transform->GetFrontVector();
    auto pos = transform->GetPosition() + front;
    auto up = transform->GetUpVector();
    return Matrix4::LookAt(pos, pos + front, up);
  }

  Math::Matrix4& Camera::GetProjectionMatrix() {
    return m_projectionMatrix;
  }

  void Camera::Update(float p_deltaTime) {
    if (gameObject->transform->isDirty || m_isDirty) {
      UpdateProjectionMatrix();
      if (true) { //TODO:: Use other APIs as well (currently using only opengl)
        RenderManager::Instance().RegisterRenderCallback([&] {
          GLShader::UpdateViewProjectionBuffer(GetViewMatrix(), GetProjectionMatrix());
          GLShader::UpdateViewPosBuffer(gameObject->transform->GetPosition());
        }, CallbackTime::PRE_RENDER, true);
      }
      m_isDirty = false;
    }

    auto transform = gameObject->transform;
  }
}
#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <GRUTMath.h>
#include "../Component.h"
#include "Scene/GameObjects/GameObject.h"

namespace GRUT {
  class Camera : public Component {
  private:
    float m_nearPlane   = 0.1f;
    float m_farPlane    = 100.0f;
    float m_orthoLeft   = 100.0f;
    float m_orthoRight  = 100.0f;
    float m_orthoTop    = 100.0f;
    float m_orthoBottom = 100.0f;
    float m_fov         = 45.0f;
    bool  m_isOrthographic = false;
    bool  m_isDirty = false;
    Math::Matrix4 m_projectionMatrix;
    void UpdateProjectionMatrix();
  public:
    const Math::Vector3 worldUp{ 0.0f, 1.0f, 0.0f };

    void Initialize() override;
    GRUT_API void SetOrtographic(bool p_val);  
    GRUT_API void SetOrthoLeft(float p_val);
    GRUT_API void SetOrthoRight(float p_val);
    GRUT_API void SetOrthoTop(float p_val);
    GRUT_API void SetOrthoBottom(float p_val);
    GRUT_API void SetNearPlane(float p_val);
    GRUT_API void SetFarPlane(float p_val);
    GRUT_API void SetFieldOfView(float p_val);
    GRUT_API Math::Matrix4 GetViewMatrix();
    GRUT_API Math::Matrix4& GetProjectionMatrix();

    void Update(float p_deltaTime) override;
  };
}
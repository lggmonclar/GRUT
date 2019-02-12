#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <GRUTMath.h>
#include "Component.h"
#include "Scene/GameObject.h"

namespace GRUT {
  class Camera : public Component {
  private:
    float m_yaw;
    float m_pitch;
    void UpdateCameraVectors();
    float m_nearPlane   = 0.1f;
    float m_farPlane    = 100.0f;
    float m_orthoLeft   = 100.0f;
    float m_orthoRight  = 100.0f;
    float m_orthoTop    = 100.0f;
    float m_orthoBottom = 100.0f;
    float m_fov         = 45.0f;
    bool  m_isOrthographic = false;
    bool  m_isDirty = false;
    Math::Matrix<4> m_projectionMatrix;
    void UpdateProjectionMatrix();
  public:
    Math::Matrix<4> view;
    Math::Vector<3> front;
    Math::Vector<3> up;
    Math::Vector<3> right;
    Math::Vector<3> worldUp;

    Camera(Math::Vector<3> pUp = Math::Vector<3>(0.0f, 1.0f, 0.0f), float pYaw = -90.0f, float pPitch = 0.0f);
    Camera(float upX, float upY, float upZ, float pYaw, float pPitch);

    void SetOrtographic(bool p_val);  
    void SetOrthoLeft(float p_val);
    void SetOrthoRight(float p_val);
    void SetOrthoTop(float p_val);
    void SetOrthoBottom(float p_val);
    void SetNearPlane(float p_val);
    void SetFarPlane(float p_val);
    void SetFieldOfView(float p_val);
    void SetYaw(float y);
    void SetPitch(float p);
    Math::Matrix<4>& GetViewMatrix();
    Math::Matrix<4>& GetProjectionMatrix();

    void Update(float p_deltaTime) override;
  };
}
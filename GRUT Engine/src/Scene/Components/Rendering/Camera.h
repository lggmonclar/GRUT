#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <GRUTMath.h>
#include "../Component.h"
#include "Scene/GameObjects/GameObject.h"

namespace GRUT {
    class Camera : public Component {
        private:
            float m_nearPlane = 0.1f;
            float m_farPlane = 100.0f;
            float m_orthoLeft = 100.0f;
            float m_orthoRight = 100.0f;
            float m_orthoTop = 100.0f;
            float m_orthoBottom = 100.0f;
            float m_fov = 45.0f;
            bool  m_isOrthographic = false;
            bool  m_isDirty = false;
            Math::Matrix4 m_projectionMatrix;
            void UpdateProjectionMatrix();

        public:
            const Math::Vector3 worldUp{ 0.0f, 1.0f, 0.0f };

            void Initialize() override;
            void SetOrtographic(bool p_val);
            void SetOrthoLeft(float p_val);
            void SetOrthoRight(float p_val);
            void SetOrthoTop(float p_val);
            void SetOrthoBottom(float p_val);
            void SetNearPlane(float p_val);
            void SetFarPlane(float p_val);
            void SetFieldOfView(float p_val);
            Math::Matrix4 GetViewMatrix();
            Math::Matrix4& GetProjectionMatrix();

            void Update(float p_deltaTime) override;
    };
}
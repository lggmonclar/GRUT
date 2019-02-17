#include "grutpch.h"
#include "RenderableComponent.h"
#include "Graphics/RenderManager.h"
#include "Graphics/Models/GLModel.h"
#include "Scene/Scene.h"
#include "Scene/GameObjects/GameObject.h"
#include "Camera.h"

namespace GRUT {
  RenderableComponent::RenderableComponent() : Component() {
    m_renderCallbackId = RenderManager::Instance().RegisterRenderCallback([&] { Render(); });
  }
  RenderableComponent::~RenderableComponent() {
    RenderManager::Instance().RemoveRenderCallback(m_renderCallbackId);
  }
  void RenderableComponent::Render() {
    auto model = gameObject->transform->modelMatrix;
    if (true) { //TODO: Implement different conditions for different graphics APIs based on configuration files
      auto shader = dynamic_cast<GLShader*>(&m_shader);
      shader->Use();
      while (!m_shaderAssignmentsCallbacks.empty()) {
        m_shaderAssignmentsCallbacks.front()();
        m_shaderAssignmentsCallbacks.pop();
      }
      shader->SetMat4("model", model);

      static_cast<GLModel*>(&m_model)->Draw(shader);
    }
  }

  void RenderableComponent::SetModel(const char * p_path) {
    if (true) { //TODO: Implement different conditions for different graphics APIs based on configuration files
      auto model = MemoryManager::Instance().AllocOnFreeList<GLModel>();
      model->LoadModel(p_path);
      m_model = model;
    }
  }
  void RenderableComponent::SetShaderType(ShaderTypes p_type) {
    m_shader = RenderManager::Instance().GetShader(p_type);
  }
  void RenderableComponent::SetModel(ObjectHandle<BaseModel> p_modelHandle) {
    m_model = p_modelHandle;
  }
  ObjectHandle<BaseModel> RenderableComponent::GetModel() {
    return m_model;
  }
  
  void RenderableComponent::SetShaderBool(const std::string & name, bool value) {
    m_shaderAssignmentsCallbacks.push([=, &m_shader = m_shader] {
      m_shader->SetBool(name, value);
    });
  }
  void RenderableComponent::SetShaderInt(const std::string & name, int value) {
    m_shaderAssignmentsCallbacks.push([=, &m_shader = m_shader] {
      m_shader->SetInt(name, value);
    });
  }
  void RenderableComponent::SetShaderFloat(const std::string & name, float value) {
    m_shaderAssignmentsCallbacks.push([=, &m_shader = m_shader] {
      m_shader->SetFloat(name, value);
    });
  }
  void RenderableComponent::SetShaderVec2(const std::string & name, const Math::Vector<2>& v2) {
    m_shaderAssignmentsCallbacks.push([=, &m_shader = m_shader] {
      m_shader->SetVec2(name, v2);
    });
  }
  void RenderableComponent::SetShaderVec2(const std::string & name, float x, float y) {
    m_shaderAssignmentsCallbacks.push([=, &m_shader = m_shader] {
      m_shader->SetVec2(name, x, y);
    });
  }
  void RenderableComponent::SetShaderVec3(const std::string & name, const Math::Vector<3>& v3) {
    m_shaderAssignmentsCallbacks.push([=, &m_shader = m_shader] {
      m_shader->SetVec3(name, v3);
    });
  }
  void RenderableComponent::SetShaderVec3(const std::string & name, float x, float y, float z) {
    m_shaderAssignmentsCallbacks.push([=, &m_shader = m_shader] {
      m_shader->SetVec3(name, x, y, z);
    });
  }
  void RenderableComponent::SetShaderVec4(const std::string & name, const Math::Vector<4>& v4) {
    m_shaderAssignmentsCallbacks.push([=, &m_shader = m_shader] {
      m_shader->SetVec4(name, v4);
    });
  }
  void RenderableComponent::SetShaderVec4(const std::string & name, float x, float y, float z, float w) {
    m_shaderAssignmentsCallbacks.push([=, &m_shader = m_shader] {
      m_shader->SetVec4(name, x, y, z, w);
    });
  }
  void RenderableComponent::SetShaderMat2(const std::string & name, const Math::Matrix<2>& m2) {
    m_shaderAssignmentsCallbacks.push([=, &m_shader = m_shader] {
      m_shader->SetMat2(name, m2);
    });
  }
  void RenderableComponent::SetShaderMat3(const std::string & name, const Math::Matrix<3>& m3) {
    m_shaderAssignmentsCallbacks.push([=, &m_shader = m_shader] {
      m_shader->SetMat3(name, m3);
    });
  }
  void RenderableComponent::SetShaderMat4(const std::string & name, const Math::Matrix<4>& m4) {
    m_shaderAssignmentsCallbacks.push([=, &m_shader = m_shader] {
      m_shader->SetMat4(name, m4);
    });
  }

  void RenderableComponent::Update(float p_deltaTime) {
    auto transform = gameObject->transform;
  }
}

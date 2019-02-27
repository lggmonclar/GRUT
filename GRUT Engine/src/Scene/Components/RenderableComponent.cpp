#include "grutpch.h"
#include "RenderableComponent.h"
#include "Graphics/RenderManager.h"
#include "Graphics/Models/GLModel.h"
#include "Scene/Scene.h"
#include "Scene/GameObjects/GameObject.h"
#include "Camera.h"

namespace GRUT {
  std::map<std::string, ObjectHandle<GLModel>> RenderableComponent::s_loadedGLModels;

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

      std::map<std::string, ShaderAssignmentCallback>::iterator i = m_shaderAssignmentsCallbacks.begin();
      while (i != m_shaderAssignmentsCallbacks.end()) {
        i->second.callback();
        if (i->second.removeAfterCall) {
          i = m_shaderAssignmentsCallbacks.erase(i);
        }
        else {
          i++;
        }
      }
      shader->SetMat4("model", model);

      static_cast<GLModel*>(&m_model)->Draw(shader);
    }
  }

  void RenderableComponent::SetModel(const char * p_path) {
    if (true) { //TODO: Implement different conditions for different graphics APIs based on configuration files
      auto existingModel = s_loadedGLModels.find(p_path);
      if (existingModel == s_loadedGLModels.end()) {
        auto model = MemoryManager::Instance().AllocOnFreeList<GLModel>();
        model->LoadModel(p_path);
        m_model = model;
        s_loadedGLModels[p_path] = model;
      }
      else {
        m_model = existingModel->second;
      }
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
  
  void RenderableComponent::SetShaderBool(const std::string & name, bool value, bool p_executeOnce) {
    m_shaderAssignmentsCallbacks[name] = { ([=, &m_shader = m_shader] {
      m_shader->SetBool(name, value);
    }), p_executeOnce};
  }
  void RenderableComponent::SetShaderInt(const std::string & name, int value, bool p_executeOnce) {
    m_shaderAssignmentsCallbacks[name] = { ([=, &m_shader = m_shader] {
      m_shader->SetInt(name, value);
    }), p_executeOnce };
  }
  void RenderableComponent::SetShaderFloat(const std::string & name, float value, bool p_executeOnce) {
    m_shaderAssignmentsCallbacks[name] = { ([=, &m_shader = m_shader] {
      m_shader->SetFloat(name, value);
    }), p_executeOnce };
  }
  void RenderableComponent::SetShaderVec2(const std::string & name, const Math::Vector<2>& v2, bool p_executeOnce) {
    m_shaderAssignmentsCallbacks[name] = { ([=, &m_shader = m_shader] {
      m_shader->SetVec2(name, v2);
    }), p_executeOnce };
  }
  void RenderableComponent::SetShaderVec2(const std::string & name, float x, float y, bool p_executeOnce) {
    m_shaderAssignmentsCallbacks[name] = { ([=, &m_shader = m_shader] {
      m_shader->SetVec2(name, x, y);
    }), p_executeOnce };
  }
  void RenderableComponent::SetShaderVec3(const std::string & name, const Math::Vector<3>& v3, bool p_executeOnce) {
    m_shaderAssignmentsCallbacks[name] = { ([=, &m_shader = m_shader] {
      m_shader->SetVec3(name, v3);
    }), p_executeOnce };
  }
  void RenderableComponent::SetShaderVec3(const std::string & name, float x, float y, float z, bool p_executeOnce) {
    m_shaderAssignmentsCallbacks[name] = { ([=, &m_shader = m_shader] {
      m_shader->SetVec3(name, x, y, z);
    }), p_executeOnce };
  }
  void RenderableComponent::SetShaderVec4(const std::string & name, const Math::Vector<4>& v4, bool p_executeOnce) {
    m_shaderAssignmentsCallbacks[name] = { ([=, &m_shader = m_shader] {
      m_shader->SetVec4(name, v4);
    }), p_executeOnce };
  }
  void RenderableComponent::SetShaderVec4(const std::string & name, float x, float y, float z, float w, bool p_executeOnce) {
    m_shaderAssignmentsCallbacks[name] = { ([=, &m_shader = m_shader] {
      m_shader->SetVec4(name, x, y, z, w);
    }), p_executeOnce };
  }
  void RenderableComponent::SetShaderMat2(const std::string & name, const Math::Matrix<2>& m2, bool p_executeOnce) {
    m_shaderAssignmentsCallbacks[name] = { ([=, &m_shader = m_shader] {
      m_shader->SetMat2(name, m2);
    }), p_executeOnce };
  }
  void RenderableComponent::SetShaderMat3(const std::string & name, const Math::Matrix<3>& m3, bool p_executeOnce) {
    m_shaderAssignmentsCallbacks[name] = { ([=, &m_shader = m_shader] {
      m_shader->SetMat3(name, m3);
    }), p_executeOnce };
  }
  void RenderableComponent::SetShaderMat4(const std::string & name, const Math::Matrix<4>& m4, bool p_executeOnce) {
    m_shaderAssignmentsCallbacks[name] = { ([=, &m_shader = m_shader] {
      m_shader->SetMat4(name, m4);
    }), p_executeOnce };
  }

  void RenderableComponent::Update(float p_deltaTime) {
    auto transform = gameObject->transform;
  }
}

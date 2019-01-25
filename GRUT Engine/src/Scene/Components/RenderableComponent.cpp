#include "grutpch.h"
#include "RenderableComponent.h"
#include "Graphics/RenderManager.h"
#include "Graphics/Models/GLModel.h"
#include "Scene/Scene.h"
#include "Scene/GameObject.h"
#include "Camera.h"

namespace GRUT {
  RenderableComponent::RenderableComponent() : Component() {
    m_callbackId = RenderManager::Instance().RegisterRenderCallback([&] { Render(); });
  }
  RenderableComponent::~RenderableComponent() {
    RenderManager::Instance().RemoveRenderCallback(m_callbackId);
  }
  void RenderableComponent::Render() {
    LOG_INFO("Called render on renderable component");
    auto model = gameObject->transform->modelMatrix;
    auto view = gameObject->scene->mainCamera->GetViewMatrix();
    auto projection = gameObject->scene->mainCamera->GetProjectionMatrix();
    if (true) { //TODO: Implement different conditions for different graphics APIs based on configuration files
      m_shader->SetMat4("mvp", model * view * projection);

      static_cast<GLModel*>(&m_model)->Draw(dynamic_cast<GLShader*>(&m_shader));
    }
  }
  void RenderableComponent::SetModel(const char * p_path) {
    if (true) { //TODO: Implement different conditions for different graphics APIs based on configuration files
      auto model = MemoryManager::Instance().AllocOnFreeList<GLModel>();
      model->LoadModel(p_path);
      m_model = model;
    }
  }
  void RenderableComponent::SetShader(const char * p_vertexPath, const char * p_fragmentPath) {
    if (true) { //TODO: Implement different conditions for different graphics APIs based on configuration files
      auto shader = MemoryManager::Instance().AllocOnFreeList<GLShader>();
      shader->LoadFragmentShader(p_fragmentPath);
      shader->LoadVertexShader(p_vertexPath);
      m_shader = shader;
    }
  }
  void RenderableComponent::SetShader(ObjectHandle<Shader> p_shader) {
    m_shader = p_shader;
  }
  void RenderableComponent::SetModel(ObjectHandle<BaseModel> p_modelHandle) {
    m_model = p_modelHandle;
  }
  ObjectHandle<BaseModel> RenderableComponent::GetModel() {
    return m_model;
  }

  ObjectHandle<Shader> RenderableComponent::GetShader() {
    return m_shader;
  }
  
}

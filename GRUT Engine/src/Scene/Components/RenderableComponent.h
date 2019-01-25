#pragma once
#include "Component.h"
#include <list>
#include <functional>
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Models/Model.h"
#include "DLLMacros.h"

namespace GRUT {
  class RenderableComponent : public Component {
  private:
    std::list<std::function<void()>>::iterator m_callbackId;
    ObjectHandle<Shader>       m_shader;
    ObjectHandle<BaseModel>    m_model;
    void Render();
  public:
    GRUT_API void SetModel(const char* p_path);
    GRUT_API void SetModel(ObjectHandle<BaseModel> p_modelHandle);
    GRUT_API void SetShader(const char * p_vertexPath, const char * p_fragmentPath);
    GRUT_API void SetShader(ObjectHandle<Shader> p_shader);
    GRUT_API ObjectHandle<BaseModel> GetModel();
    GRUT_API ObjectHandle<Shader> GetShader();
    GRUT_API RenderableComponent();
    ~RenderableComponent();
  };
}
#pragma once
#include "Component.h"
#include <list>
#include <queue>
#include <functional>
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Models/Model.h"
#include "Graphics/Shaders/ShaderTypes.h"
#include "DLLMacros.h"

namespace GRUT {
  struct RenderCallback;
  class RenderableComponent : public Component {
  private:
    std::list<RenderCallback>::iterator m_renderCallbackId;
    std::queue<std::function<void()>> m_shaderAssignmentsCallbacks;
    ObjectHandle<Shader>       m_shader;
    ObjectHandle<BaseModel>    m_model;
    void Render();
  public:
    GRUT_API void SetModel(const char* p_path);
    GRUT_API void SetModel(ObjectHandle<BaseModel> p_modelHandle);
    GRUT_API void SetShaderType(ShaderTypes p_type);
    GRUT_API ObjectHandle<BaseModel> GetModel();
    GRUT_API RenderableComponent();
    GRUT_API void SetShaderBool(const std::string &name, bool value);
    GRUT_API void SetShaderInt(const std::string &name, int value);
    GRUT_API void SetShaderFloat(const std::string &name, float value);
    GRUT_API void SetShaderVec2(const std::string &name, const Math::Vector<2> &v2);
    GRUT_API void SetShaderVec2(const std::string &name, float x, float y);
    GRUT_API void SetShaderVec3(const std::string &name, const Math::Vector<3> &v3);
    GRUT_API void SetShaderVec3(const std::string &name, float x, float y, float z);
    GRUT_API void SetShaderVec4(const std::string &name, const Math::Vector<4> &v4);
    GRUT_API void SetShaderVec4(const std::string &name, float x, float y, float z, float w);
    GRUT_API void SetShaderMat2(const std::string &name, const Math::Matrix<2> &mat);
    GRUT_API void SetShaderMat3(const std::string &name, const Math::Matrix<3> &m3);
    GRUT_API void SetShaderMat4(const std::string &name, const Math::Matrix<4> &m4);
    void Update(float p_deltaTime) override;
    ~RenderableComponent();
  };
}
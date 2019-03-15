#pragma once
#include "../Component.h"
#include <list>
#include <queue>
#include <functional>
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Models/Model.h"
#include "Graphics/Shaders/ShaderTypes.h"
#include "DLLMacros.h"

namespace GRUT {
  struct RenderCallback;
  class GLModel;
  
  struct ShaderAssignmentCallback {
    std::function<void()> callback;
    bool removeAfterCall = false;
  };

  class RenderableComponent : public Component {
  private:
    std::list<RenderCallback>::iterator m_renderCallbackId;
    std::map<std::string, ShaderAssignmentCallback> m_shaderAssignmentsCallbacks;

    static std::map<std::string, ObjectHandle<GLModel>> s_loadedGLModels;
    ObjectHandle<Shader>       m_shader;
    ObjectHandle<BaseModel>    m_model;
    void Render();
  public:
    GRUT_API void Initialize() override;
    GRUT_API void SetModel(const char* p_path);
    GRUT_API void SetModel(ObjectHandle<BaseModel> p_modelHandle);
    GRUT_API void SetShaderType(ShaderTypes p_type);
    GRUT_API ObjectHandle<BaseModel> GetModel();
    GRUT_API void SetShaderBool(const std::string &name, bool value, bool p_executeOnce = false);
    GRUT_API void SetShaderInt(const std::string &name, int value, bool p_executeOnce = false);
    GRUT_API void SetShaderFloat(const std::string &name, float value, bool p_executeOnce = false);
    GRUT_API void SetShaderVec2(const std::string &name, const Math::Vector<2> &v2, bool p_executeOnce = false);
    GRUT_API void SetShaderVec2(const std::string &name, float x, float y, bool p_executeOnce = false);
    GRUT_API void SetShaderVec3(const std::string &name, const Math::Vector<3> &v3, bool p_executeOnce = false);
    GRUT_API void SetShaderVec3(const std::string &name, float x, float y, float z, bool p_executeOnce = false);
    GRUT_API void SetShaderVec4(const std::string &name, const Math::Vector<4> &v4, bool p_executeOnce = false);
    GRUT_API void SetShaderVec4(const std::string &name, float x, float y, float z, float w, bool p_executeOnce = false);
    GRUT_API void SetShaderMat2(const std::string &name, const Math::Matrix<2> &mat, bool p_executeOnce = false);
    GRUT_API void SetShaderMat3(const std::string &name, const Math::Matrix<3> &m3, bool p_executeOnce = false);
    GRUT_API void SetShaderMat4(const std::string &name, const Math::Matrix<4> &m4, bool p_executeOnce = false);
    GRUT_API void Update(float p_deltaTime) override;
    ~RenderableComponent();
  };
}
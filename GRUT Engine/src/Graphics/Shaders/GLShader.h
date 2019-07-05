#pragma once
#include <GRUTMath.h>
#include "Core/Memory/ObjectHandle.h"
#include "IShader.h"

namespace GRUT {
  class Light;
  class GLShader : public IShader {
  private:
    unsigned int m_vShaderProgram;
    unsigned int m_fShaderProgram;
  protected:
    bool CompileVertexShader(const char* p_vertexCode) override;
    bool CompileFragmentShader(const char* p_fragmentCode) override;
    bool CheckCompileErrors(unsigned int shader, const std::string &type) override;
    static unsigned int s_ssboPointLights;
    static unsigned int s_uboViewPos;
    static unsigned int s_uboViewProjection;
  public:
    unsigned int ID = 0;
    GLShader() = default;

    void Use();
    void SetBool(const std::string &name, bool value) const override;
    void SetInt(const std::string &name, int value) const override;
    void SetFloat(const std::string &name, float value) const override;
    void SetVec2(const std::string &name, const Math::Vector2 &v2) const override;
    void SetVec2(const std::string &name, float x, float y) const override;
    void SetVec3(const std::string &name, const Math::Vector3 &v3) const override;
    void SetVec3(const std::string &name, float x, float y, float z) const override;
    void SetVec4(const std::string &name, const Math::Vector4 &v4) const override;
    void SetVec4(const std::string &name, float x, float y, float z, float w) const override;
    void SetMat4(const std::string &name, const Math::Matrix4 &m4) const override;
    static void UpdateViewProjectionBuffer(const Math::Matrix4 &p_view, const Math::Matrix4 &p_projection);
    static void UpdateViewPosBuffer(const Math::Vector3 &p_viewPos);
    static void UpdatePointLightsBuffer(const std::vector<ObjectHandle<Light>> &p_pointLights);
  };
}
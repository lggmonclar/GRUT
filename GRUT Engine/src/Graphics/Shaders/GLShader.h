#pragma once
#include <GRUTMath.h>
#include "Core/Memory/ObjectHandle.h"
#include "Shader.h"

namespace GRUT {
  class Light;
  class GLShader : public Shader {
  private:
    unsigned int m_vShaderProgram;
    unsigned int m_fShaderProgram;
  protected:
    GRUT_API void CompileVertexShader(const char* p_vertexCode) override;
    GRUT_API void CompileFragmentShader(const char* p_fragmentCode) override;
    GRUT_API void CheckCompileErrors(unsigned int shader, std::string type) override;
    static unsigned int s_ssboPointLights;
    static unsigned int s_uboViewPos;
    static unsigned int s_uboViewProjection;
  public:
    unsigned int ID = 0;
    GLShader() = default;

    GRUT_API void Use();
    GRUT_API void SetBool(const std::string &name, bool value) const override;
    GRUT_API void SetInt(const std::string &name, int value) const override;
    GRUT_API void SetFloat(const std::string &name, float value) const override;
    GRUT_API void SetVec2(const std::string &name, const Math::Vector<2> &v2) const override;
    GRUT_API void SetVec2(const std::string &name, float x, float y) const override;
    GRUT_API void SetVec3(const std::string &name, const Math::Vector<3> &v3) const override;
    GRUT_API void SetVec3(const std::string &name, float x, float y, float z) const override;
    GRUT_API void SetVec4(const std::string &name, const Math::Vector<4> &v4) const override;
    GRUT_API void SetVec4(const std::string &name, float x, float y, float z, float w) const override;
    GRUT_API void SetMat2(const std::string &name, const Math::Matrix<2> &mat) const override;
    GRUT_API void SetMat3(const std::string &name, const Math::Matrix<3> &m3) const override;
    GRUT_API void SetMat4(const std::string &name, const Math::Matrix<4> &m4) const override;
    GRUT_API static void UpdateViewProjectionBuffer(const Math::Matrix<4> &p_view, const Math::Matrix<4> &p_projection);
    GRUT_API static void UpdateViewPosBuffer(const Math::Vector<3> &p_viewPos);
    GRUT_API static void UpdatePointLightsBuffer(const std::vector<ObjectHandle<Light>> &p_pointLights);
  };
}
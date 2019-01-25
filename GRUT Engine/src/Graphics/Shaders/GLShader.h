#pragma once
#include <GRUTMath.h>
#include "Shader.h"

namespace GRUT {
  class GLShader : public Shader {
  private:
    unsigned int m_vShaderProgram;
    unsigned int m_fShaderProgram;
  protected:
    void CompileVertexShader(const char* p_vertexCode) override;
    void CompileFragmentShader(const char* p_fragmentCode) override;
    void CheckCompileErrors(unsigned int shader, std::string type) override;
  public:
    unsigned int ID = 0;
    GLShader() = default;

    void Use();
    void SetBool(const std::string &name, bool value) const override;
    void SetInt(const std::string &name, int value) const override;
    void SetFloat(const std::string &name, float value) const override;
    void SetVec2(const std::string &name, const Math::Vector<2> &v2) const override;
    void SetVec2(const std::string &name, float x, float y) const override;
    void SetVec3(const std::string &name, const Math::Vector<3> &v3) const override;
    void SetVec3(const std::string &name, float x, float y, float z) const override;
    void SetVec4(const std::string &name, const Math::Vector<4> &v4) const override;
    void SetVec4(const std::string &name, float x, float y, float z, float w) const override;
    void SetMat2(const std::string &name, const Math::Matrix<2> &mat) const override;
    void SetMat3(const std::string &name, const Math::Matrix<3> &m3) const override;
    void SetMat4(const std::string &name, const Math::Matrix<4> &m4) const override;
  };
}
#pragma once
#include <GRUTMath.h>
#include <string>

namespace GRUT {
  class Shader {
  private:
    std::string LoadFileContents(const char* path);
  protected:
    virtual void CompileVertexShader(const char* p_vertexCode) = 0;
    virtual void CompileFragmentShader(const char* p_fragmentCode) = 0;
    virtual void CheckCompileErrors(unsigned int shader, std::string type) = 0;
  public:
    Shader() = default;
    GRUT_API bool LoadVertexShader(const char* path);
    GRUT_API bool LoadFragmentShader(const char* path);

    virtual void SetBool(const std::string &name, bool value) const = 0;
    virtual void SetInt(const std::string &name, int value) const = 0;
    virtual void SetFloat(const std::string &name, float value) const = 0;
    virtual void SetVec2(const std::string &name, const Math::Vector<2> &v2) const = 0;
    virtual void SetVec2(const std::string &name, float x, float y) const = 0;
    virtual void SetVec3(const std::string &name, const Math::Vector<3> &v3) const = 0;
    virtual void SetVec3(const std::string &name, float x, float y, float z) const = 0;
    virtual void SetVec4(const std::string &name, const Math::Vector<4> &v4) const = 0;
    virtual void SetVec4(const std::string &name, float x, float y, float z, float w) const = 0;
    virtual void SetMat2(const std::string &name, const Math::Matrix<2> &mat) const = 0;
    virtual void SetMat3(const std::string &name, const Math::Matrix<3> &m3) const = 0;
    virtual void SetMat4(const std::string &name, const Math::Matrix<4> &m4) const = 0;
  };
}
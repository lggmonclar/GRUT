#include "grutpch.h"
#include "GLShader.h"
#include "Graphics/Windows/GLWindow.h"
#include "Graphics/RenderManager.h"

namespace GRUT {
  void GLShader::CompileVertexShader(const char * p_vertexCode) {
    auto window = dynamic_cast<GLWindow*>(RenderManager::Instance().GetWindow().get());
    window->SetContext();
    m_vShaderProgram = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vShaderProgram, 1, &p_vertexCode, NULL);
    glCompileShader(m_vShaderProgram);
    CheckCompileErrors(m_vShaderProgram, "VERTEX");
    window->ClearContext();
  }
  void GLShader::CompileFragmentShader(const char * p_fragmentCode) {
    auto window = dynamic_cast<GLWindow*>(RenderManager::Instance().GetWindow().get());
    window->SetContext();
    m_fShaderProgram = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fShaderProgram, 1, &p_fragmentCode, NULL);
    glCompileShader(m_fShaderProgram);
    CheckCompileErrors(m_fShaderProgram, "FRAGMENT");
    window->ClearContext();
  }
  void GLShader::CheckCompileErrors(unsigned int p_shader, std::string p_type) {
    int success;
    char infoLog[1024];
    if (p_type != "PROGRAM") {
      glGetShaderiv(p_shader, GL_COMPILE_STATUS, &success);
      if (!success) {
        glGetShaderInfoLog(p_shader, 1024, NULL, infoLog);
        LOG_ERROR("Shader compilation error of type {0}", p_type);
        LOG_INFO("{0}", infoLog);
      }
    }
    else {
      glGetProgramiv(p_shader, GL_LINK_STATUS, &success);
      if (!success) {
        glGetProgramInfoLog(p_shader, 1024, NULL, infoLog);       
        LOG_ERROR("Program linking error of type {0}", p_type);
        LOG_INFO("{0}", infoLog);
      }
    }
  }
  void GLShader::Use() {
    if (!ID) {
      ID = glCreateProgram();
      glAttachShader(ID, m_vShaderProgram);
      glAttachShader(ID, m_fShaderProgram);
      glLinkProgram(ID);
      CheckCompileErrors(ID, "PROGRAM");

      glDeleteShader(m_vShaderProgram);
      glDeleteShader(m_fShaderProgram);
    }
    glUseProgram(ID);
  }

  void GLShader::SetBool(const std::string & name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
  }
  void GLShader::SetInt(const std::string & name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }
  void GLShader::SetFloat(const std::string & name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }
  void GLShader::SetVec2(const std::string & name, const Math::Vector<2>& v2) const {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, v2);
  }
  void GLShader::SetVec2(const std::string & name, float x, float y) const {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
  }
  void GLShader::SetVec3(const std::string & name, const Math::Vector<3>& v3) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, v3);
  }
  void GLShader::SetVec3(const std::string & name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
  }
  void GLShader::SetVec4(const std::string & name, const Math::Vector<4>& v4) const {
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, v4);
  }
  void GLShader::SetVec4(const std::string & name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
  }
  void GLShader::SetMat2(const std::string & name, const Math::Matrix<2>& m2) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, m2);
  }
  void GLShader::SetMat3(const std::string & name, const Math::Matrix<3>& m3) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, m3);
  }
  void GLShader::SetMat4(const std::string & name, const Math::Matrix<4>& m4) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, m4);
  }
}

#include "grutpch.h"
#include "Shader.h"
#include "Core/Jobs/JobManager.h"
#include "Graphics/RenderManager.h"

namespace GRUT {
  void Shader::LoadVertexShader(const char * path) {
    RenderManager::Instance().RegisterRenderCallback([=] {
      std::string contents = LoadFileContents(path);

      if (contents.empty()) {
        LOG_ERROR("{0} File contents are empty", path);
        return;
      }
    
      CompileVertexShader(contents.c_str());
    }, CallbackTime::PRE_RENDER, true);
  }
  void Shader::LoadFragmentShader(const char * path) {
    RenderManager::Instance().RegisterRenderCallback([=] {
      std::string contents = LoadFileContents(path);

      if (contents.empty()) {
        LOG_ERROR("{0} File contents are empty", path);
        return;
      }

      CompileFragmentShader(contents.c_str());
    }, CallbackTime::PRE_RENDER, true);
  }
  std::string Shader::LoadFileContents(const char * path) {
    std::ifstream fileStream;
    std::stringstream stringStream;

    fileStream.open(path);
    if (fileStream.bad()) {
      LOG_ERROR("Failed to open shader file");
      LOG_ERROR("File was {0}", path);
      return "";
    }
    stringStream << fileStream.rdbuf();
    fileStream.close();

    return stringStream.str();
  }
}
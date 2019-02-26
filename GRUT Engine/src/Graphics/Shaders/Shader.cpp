#include "grutpch.h"
#include "Shader.h"
#include "Core/Jobs/JobManager.h"
#include "Graphics/RenderManager.h"

namespace GRUT {
  bool Shader::LoadVertexShader(const char * path) {
    std::string contents;
    auto jobPtr = JobManager::Instance().KickJob([&]() {
      contents = LoadFileContents(path);
    });

    JobManager::Instance().WaitForJob(jobPtr);
    if (contents.empty())
      return false;
    
    RenderManager::Instance().RegisterRenderCallback([=] {
      CompileVertexShader(contents.c_str());
    }, CallbackTime::PRE_RENDER, true);
    return true;
  }
  bool Shader::LoadFragmentShader(const char * path) {
    std::string contents;
    auto jobPtr = JobManager::Instance().KickJob([&]() {
      contents = LoadFileContents(path);
    });

    JobManager::Instance().WaitForJob(jobPtr);
    if (contents.empty())
      return false;

    RenderManager::Instance().RegisterRenderCallback([=] {
      CompileFragmentShader(contents.c_str());
    }, CallbackTime::PRE_RENDER, true);
    return true;
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
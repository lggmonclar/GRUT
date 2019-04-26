#include "grutpch.h"
#include "IShader.h"
#include "Core/Jobs/JobManager.h"
#include "Graphics/RenderManager.h"
#include "Core/FileSystem.h"

namespace GRUT {
  void IShader::LoadVertexShader(const char * path) {
    RenderManager::Instance().RegisterRenderCallback([=] {
      std::string contents = FileSystem::LoadFileContents(path);

      if (contents.empty()) {
        LOG_ERROR("{0} File contents are empty", path);
        return;
      }
    
      CompileVertexShader(contents.c_str());
    }, CallbackTime::PRE_RENDER, true);
  }
  void IShader::LoadFragmentShader(const char * path) {
    RenderManager::Instance().RegisterRenderCallback([=] {
      std::string contents = FileSystem::LoadFileContents(path);

      if (contents.empty()) {
        LOG_ERROR("{0} File contents are empty", path);
        return;
      }

      CompileFragmentShader(contents.c_str());
    }, CallbackTime::PRE_RENDER, true);
  }
}
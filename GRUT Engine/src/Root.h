#pragma once
#include "grutpch.h"
#include "DLLMacros.h"
#include "Graphics/RenderManager.h"
#include "Input/InputManager.h"

namespace GRUT {
  class Root {
  private:
    std::shared_ptr<Window> window;
    RenderManager renderManager;
    InputManager  inputManager;
    const std::shared_ptr<Window> InitializeWindow();
  public:
    GRUT_API Root();
    GRUT_API virtual ~Root();
    GRUT_API void Run();
  };

  Root* CreateApplication();
}
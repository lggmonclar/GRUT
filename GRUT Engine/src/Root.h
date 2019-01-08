#pragma once
#include "grutpch.h"
#include "Job.h"
#include "DLLMacros.h"
#include "RenderManager.h"
#include "InputManager.h"

namespace GRUT {
  class Root {
  private:
    std::shared_ptr<Window> window;
    RenderManager renderManager;
    InputManager  inputManager;
  public:
    GRUT_API Root();
    GRUT_API virtual ~Root();
    GRUT_API void Run();
    GRUT_API const std::shared_ptr<Window> InitializeWindow();
  };

  Root* CreateApplication();
}
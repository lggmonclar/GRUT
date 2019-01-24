#pragma once
#include "DLLMacros.h"
#include "Input/InputManager.h"
#include "Core/Parallelism/FrameParams.h"

namespace GRUT {
  class Root {
  private:
    std::shared_ptr<Window> window;
    InputManager  inputManager;
    const std::shared_ptr<Window> InitializeWindow();
    FrameParams frames[16];
  public:
    GRUT_API Root();
    GRUT_API virtual ~Root();
    GRUT_API void Run();
    GRUT_API static class Clock& GetGameClock();
  };

  Root* CreateApplication();
}
#pragma once
#include "DLLMacros.h"
#include "Input/InputManager.h"
#include "Core/Parallelism/FrameParams.h"
#include "Config.h"

namespace GRUT {
  class Root {
  public:
    GRUT_API Root();
    GRUT_API virtual ~Root();
    GRUT_API void Run();
    GRUT_API static class Clock& GetGameClock();
  private:
    std::shared_ptr<Window> window;
    const std::shared_ptr<Window> InitializeWindow();
    FrameParams frames[Config::FRAME_PARAMS_COUNT];
  };

  Root* CreateApplication();
}
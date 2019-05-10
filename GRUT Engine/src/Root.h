#pragma once
#include "DLLMacros.h"
#include "Input/InputManager.h"
#include "Core/Parallelism/FrameParams.h"
#include "Core/Config/CVar.h"

namespace GRUT {
  class Root {
  public:
    GRUT_API Root();
    GRUT_API virtual ~Root();
    GRUT_API void Run();
    GRUT_API static class Clock& GetGameClock();
  private:
    std::shared_ptr<IWindow> window;
    const std::shared_ptr<IWindow> InitializeWindow();
  };

  Root* CreateApplication();
}
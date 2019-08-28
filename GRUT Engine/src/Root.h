#pragma once
#include "DLLMacros.h"
#include "Input/InputManager.h"
#include "Core/Parallelism/FrameParams.h"
#include "Core/Config/CVar.h"

namespace GRUT {
  class Root {
  public:
    Root();
    virtual ~Root();
    void Run();
    static class Clock& GetGameClock();
  private:
    std::shared_ptr<IWindow> m_window;
    FrameParams* m_frames;
    const std::shared_ptr<IWindow> InitializeWindow();
  };

  Root* CreateApplication();
}
#pragma once
#include "Window.h"
#include "Core/Parallelism/UnnecessaryLock.h"

namespace GRUT {
  class GLWindow : public Window {
  private:
    UnnecessaryLock m_lock;
    GLFWwindow* m_window;
  public:
    GLWindow();
    ~GLWindow();
    void SetContext();
    void ClearContext();
    void BeginFrame() override;
    void EndFrame() override;
    void PollEvents() override;
    bool ShouldClose() override;
  };
};
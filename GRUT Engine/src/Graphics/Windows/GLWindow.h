#pragma once
#include "Window.h"

namespace GRUT {
  class GLWindow : public Window {
  private:
    GLFWwindow* m_window;
  public:
    GLWindow();
    ~GLWindow();
    void BeginFrame() override;
    void EndFrame() override;
    void PollEvents() override;
    bool ShouldClose() override;
  };
};
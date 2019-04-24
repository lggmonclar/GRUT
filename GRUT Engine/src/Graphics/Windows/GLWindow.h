#pragma once
#include "Window.h"

namespace GRUT {
  class GLWindow : public Window {
  private:
    GLFWwindow* m_window;
  public:
    GLWindow();
    ~GLWindow();
    void* GetNativeWindow() override;
    void BeginFrame() override;
    void EndFrame() override;
    void PollEvents() override;
    bool ShouldClose() override;
  };
};
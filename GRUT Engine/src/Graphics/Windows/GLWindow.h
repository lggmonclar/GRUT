#pragma once
#include "IWindow.h"

namespace GRUT {
  class GLWindow : public IWindow {
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
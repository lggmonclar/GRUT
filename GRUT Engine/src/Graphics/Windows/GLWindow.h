#pragma once
#include "Window.h"
#include "Core/Parallelism/UnnecessaryLock.h"

namespace GRUT {
  class GLWindow : public Window {
  private:
    UnnecessaryLock m_lock;
    GLFWwindow* m_window;
    std::function<void(KeyboardEvent)> m_keyboardCallback = nullptr;
    std::function<void(MouseEvent)> m_mouseCallback = nullptr;
  public:
    GLWindow();
    ~GLWindow();
    void SetContext();
    void ClearContext();
    void BeginFrame() override;
    void EndFrame() override;
    void SetKeyboardCallback(std::function<void(KeyboardEvent)>) override;
    void SetMouseCallback(std::function<void(MouseEvent)>) override;
    void PollEvents() override;
    bool ShouldClose() override;
  };
};
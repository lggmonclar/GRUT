#pragma once
#include "grutpch.h"
#include "Graphics/Windows/Window.h"

namespace GRUT {
  class InputManager {
  private:
    std::shared_ptr<Window> m_window;
  protected:
  public:
    InputManager() = default;
    ~InputManager() = default;
    void SetWindow(std::shared_ptr<Window> p_window);
    void PollInputs();
  };
};
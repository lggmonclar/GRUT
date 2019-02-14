#pragma once
#include <memory>
#include "Graphics/Windows/Window.h"

namespace GRUT {
  enum class Keys;
  enum class States;
  enum class MouseButtons;
  class InputManager {
  private:
    std::shared_ptr<Window> m_window;
    InputManager() = default;
    ~InputManager() = default;
  public:
    GRUT_API static InputManager& Instance() {
      static InputManager instance{};
      return instance;
    }
    static void Initialize(std::shared_ptr<Window> p_window);
    void ProcessKeyboardEvent(Keys p_key, States p_action);
    void ProcessMouseEvent(MouseButtons p_button, States p_action);
    void ProcessMouseMovement(const double &p_xPos, const double &p_yPos);
    void PollInputs();
  };
};
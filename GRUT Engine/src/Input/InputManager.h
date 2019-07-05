#pragma once
#include <memory>
#include "Graphics/Windows/IWindow.h"

namespace GRUT {
  enum class Keys;
  enum class States;
  enum class MouseButtons;
  class InputManager {
  private:
    std::shared_ptr<IWindow> m_window;
    InputManager() = default;
    ~InputManager() = default;
  public:
    static InputManager& Instance() {
      static InputManager instance{};
      return instance;
    }
    static void Initialize(std::shared_ptr<IWindow> p_window);
    void ProcessKeyboardEvent(Keys p_key, States p_action);
    void ProcessMouseEvent(MouseButtons p_button, States p_action);
    void ProcessMouseMovement(const double &p_xPos, const double &p_yPos);
    void PollInputs();
  };
};
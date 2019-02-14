#include "grutpch.h"
#include "Input.h"

namespace GRUT {
  std::map<Keys, States> Input::s_keyStates;
  std::map<MouseButtons, States> Input::s_mouseButtonStates;
  double Input::mouseX = 0.0f;
  double Input::mouseY = 0.0f;

  void Input::SetKeyState(Keys p_key, States p_state) {
    s_keyStates[p_key] = p_state;
  }
  void Input::SetMouseState(MouseButtons p_button, States p_state) {
    s_mouseButtonStates[p_button] = p_state;
  }

  void Input::SetMousePosition(const double &p_xPos, const double &p_yPos) {
    mouseX = p_xPos;
    mouseY = p_yPos;
  }

  bool Input::GetKeyDown(Keys p_key) {
    return s_keyStates[p_key] == States::PRESS || s_keyStates[p_key] == States::REPEAT;
  }
  bool Input::GetKeyUp(Keys p_key) {
    return s_keyStates[p_key] == States::RELEASE;
  }

  bool Input::GetMouseButtonDown(MouseButtons p_button) {
    return s_mouseButtonStates[p_button] == States::PRESS || s_mouseButtonStates[p_button] == States::REPEAT;
  }
  bool Input::GetMouseButtonUp(MouseButtons p_button) {
    return s_mouseButtonStates[p_button] == States::RELEASE;
  }
}

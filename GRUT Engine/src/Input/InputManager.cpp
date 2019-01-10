#include "grutpch.h"
#include "InputManager.h"

namespace GRUT {
  void InputManager::SetWindow(std::shared_ptr<Window> p_window) {
    m_window = p_window;
  }
  void InputManager::PollInputs() {
    m_window->PollEvents();
  }
}
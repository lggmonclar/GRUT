#include "grutpch.h"
#include "InputManager.h"
#include "Core/Jobs/JobManager.h"
#include "Input.h"

namespace GRUT {
    void InputManager::Initialize(std::shared_ptr<IWindow> p_window) {
        Instance().m_window = p_window;
    }
    void InputManager::PollInputs() {
        m_window->PollEvents();
    }
    void InputManager::ProcessKeyboardEvent(Keys p_key, States p_state) {
        Input::SetKeyState(p_key, p_state);
    }
    void InputManager::ProcessMouseEvent(MouseButtons p_button, States p_state) {
        Input::SetMouseState(p_button, p_state);
    }
    void InputManager::ProcessMouseMovement(const double& p_xPos, const double& p_yPos) {
        Input::SetMousePosition(p_xPos, p_yPos);
    }
}
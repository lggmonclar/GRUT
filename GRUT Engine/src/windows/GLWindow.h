#pragma once
#include "Window.h"
#include <GLFW/glfw3.h>

namespace GRUT {
	class GLWindow : public Window {
	private:
		GLFWwindow* m_window;
		std::function<void(KeyboardEvent)> m_keyboardCallback = nullptr;
		std::function<void(MouseEvent)> m_mouseCallback = nullptr;
	public:
		GLWindow();
		~GLWindow();
		void Draw() override;
		void SetKeyboardCallback(std::function<void(KeyboardEvent)>) override;
		void SetMouseCallback(std::function<void(MouseEvent)>) override;
		void PollEvents() override;
	};
};
#pragma once
#include "KeyboardEvent.h"
#include "MouseEvent.h"

namespace GRUT {
	class Window {
	private:
	public:
		virtual void Draw() = 0;
		virtual void SetKeyboardCallback(std::function<void(KeyboardEvent)>) = 0;
		virtual void SetMouseCallback(std::function<void(MouseEvent)>) = 0;
		virtual void PollEvents() = 0;
	};
};
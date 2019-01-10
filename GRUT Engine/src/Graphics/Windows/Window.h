#pragma once
#include "Input/KeyboardEvent.h"
#include "Input/MouseEvent.h"

namespace GRUT {
  class Window {
  private:
  public:
    virtual void Draw() = 0;
    virtual void SetKeyboardCallback(std::function<void(KeyboardEvent)>) = 0;
    virtual void SetMouseCallback(std::function<void(MouseEvent)>) = 0;
    virtual void PollEvents() = 0;
    virtual bool ShouldClose() = 0;
  };
};
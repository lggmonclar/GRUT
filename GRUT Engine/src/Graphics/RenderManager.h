#pragma once
#include "Windows/Window.h"

namespace GRUT {
  class RenderManager {
  private:
    std::shared_ptr<Window> m_window;
  protected:
  public:
    RenderManager() = default;
    ~RenderManager() = default;
    void SetWindow(std::shared_ptr<Window> p_window);
    void Draw();
  };
};
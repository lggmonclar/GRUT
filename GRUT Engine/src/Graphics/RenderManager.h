#pragma once
#include "Windows/Window.h"
#include "Core/Parallelism/SpinLock.h"

namespace GRUT {
  struct FrameParams;
  class RenderManager {
  private:
    std::shared_ptr<Window> m_window;
  protected:
  public:  
    int idx = 0;
    RenderManager() = default;
    ~RenderManager() = default;
    void Initialize(std::shared_ptr<Window> p_window);
    void DrawFrame(FrameParams& p_prevFrame, FrameParams& p_currFrame);
  };
};
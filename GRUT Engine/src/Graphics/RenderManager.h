#pragma once
#include "Windows/Window.h"
#include "Core/Parallelism/SpinLock.h"

namespace GRUT {
  struct FrameParams;
  class RenderManager {
  private:
    std::shared_ptr<Window> m_window;
    std::list<std::function<void()>> m_renderCallbacks;
    RenderManager() = default;
    ~RenderManager() = default;
    int m_idx = 0;
  public:
    inline std::shared_ptr<Window> GetWindow() { return m_window; }
    static RenderManager& Instance() {
      static RenderManager instance{};
      return instance;
    }
    static void Initialize(std::shared_ptr<Window> p_window);
    std::list<std::function<void()>>::iterator RegisterRenderCallback(std::function<void()> p_callback);
    void RemoveRenderCallback(std::list<std::function<void()>>::iterator p_index);
    void DrawFrame(FrameParams& p_prevFrame, FrameParams& p_currFrame);
  };
};
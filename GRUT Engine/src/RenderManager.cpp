#include "grutpch.h"
#include "RenderManager.h"
#include "JobManager.h"

namespace GRUT {
  void RenderManager::SetWindow(std::shared_ptr<Window> p_window) {
    m_window = p_window;
  }
  void RenderManager::Draw() {
    m_window->Draw();
  }
}

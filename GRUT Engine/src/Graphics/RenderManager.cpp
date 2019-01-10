#include "grutpch.h"
#include "RenderManager.h"

namespace GRUT {
  void RenderManager::SetWindow(std::shared_ptr<Window> p_window) {
    m_window = p_window;
  }
  void RenderManager::Draw() {
    if(!m_window || m_window->ShouldClose())
      return;
    m_window->Draw();
  }
}

#include "grutpch.h"
#include "RenderManager.h"
#include "Core/Jobs/JobManager.h"

namespace GRUT {
  std::weak_ptr<Job> prevFrameJob;

  void RenderManager::Initialize(std::shared_ptr<Window> p_window) {
    m_window = p_window;
  }
  void RenderManager::DrawFrame() {
    JobManager::Instance().KickJob(Job([&, m_window = m_window](std::shared_ptr<Job> p) {
      p->WaitForJob(prevFrameJob);
      prevFrameJob = p;
      //Timer t("Render");

      m_window->BeginFrame();

      //Draw objects

      m_window->EndFrame();
    }));
  }
}
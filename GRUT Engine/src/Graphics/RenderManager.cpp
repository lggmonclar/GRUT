#include "grutpch.h"
#include "RenderManager.h"
#include "Core/Jobs/JobManager.h"
#include "Core/Parallelism/FrameParams.h"

namespace GRUT {
  void RenderManager::Initialize(std::shared_ptr<Window> p_window) {
    RenderManager::Instance().m_window = p_window;
  }
  std::list<std::function<void()>>::iterator RenderManager::RegisterRenderCallback(std::function<void()> p_callback) {
    return m_renderCallbacks.insert(m_renderCallbacks.end(), p_callback);
  }
  void RenderManager::RemoveRenderCallback(std::list<std::function<void()>>::iterator p_index) {
    m_renderCallbacks.erase(p_index);
  }

  void RenderManager::DrawFrame(FrameParams& p_prevFrame, FrameParams& p_currFrame) {
    p_currFrame.renderJob = JobManager::Instance().KickJob([&, m_window = m_window]() {
      JobManager::Instance().WaitForJobs({ p_currFrame.updateJob, p_prevFrame.renderJob });
      LOG_DEBUG("render {0}", m_idx);

      m_window->BeginFrame();

      //Draw objects
      for (auto &cb : m_renderCallbacks) {
        cb();
      }

      m_window->EndFrame();

      LOG_DEBUG("render {0}", m_idx++);
    });
  }
}
#include "grutpch.h"
#include "RenderManager.h"
#include "Core/Jobs/JobManager.h"
#include "Core/Parallelism/FrameParams.h"

namespace GRUT {
  void RenderManager::Initialize(std::shared_ptr<Window> p_window) {
    m_window = p_window;
  }

  void RenderManager::DrawFrame(FrameParams& p_prevFrame, FrameParams& p_currFrame) {
    p_currFrame.renderJob = JobManager::Instance().KickJob(Job([&, m_window = m_window](std::shared_ptr<Job> p) {
      p->WaitForJobs({ p_currFrame.updateJob, p_prevFrame.renderJob });
      LOG_DEBUG("render {0}", idx);

      m_window->BeginFrame();

      //Draw objects

      m_window->EndFrame();

      LOG_DEBUG("render {0}", idx++);
    }));
  }
}
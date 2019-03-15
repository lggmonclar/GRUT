#include "grutpch.h"
#include "RenderManager.h"
#include "Core/Jobs/JobManager.h"
#include "Core/Parallelism/FrameParams.h"

#include "Models/GLModel.h"
#include "Shaders/GLShader.h"
#include "Scene/Components/Rendering/Camera.h"
#include <math.h>

namespace GRUT {
  void RenderManager::ExecuteCallbacks(std::list<RenderCallback>& p_callbackList) {
    std::list<RenderCallback>::iterator i = p_callbackList.begin();
    while (i != p_callbackList.end()) {
      i->callback();
      if (i->removeAfterCall) {
        i = p_callbackList.erase(i);
      }
      else {
        i++;
      }
    }
  }

  void RenderManager::Initialize(std::shared_ptr<Window> p_window) {
    Instance().m_window = p_window;
    if (true) {//TODO: Config for different apis
      Instance().LoadShaders<GLShader>();
    }
  }
  std::list<RenderCallback>::iterator RenderManager::RegisterRenderCallback(std::function<void()> p_callback, CallbackTime p_time, bool p_callOnce) {
    std::list<RenderCallback>::iterator iterator;
    switch (p_time) {
    case CallbackTime::PRE_RENDER:
      iterator = m_preRenderCallbacks.insert(m_preRenderCallbacks.end(), { p_callback, p_callOnce });
      break;
    case CallbackTime::RENDER:
      iterator = m_renderCallbacks.insert(m_renderCallbacks.end(), { p_callback, p_callOnce });
      break;
    case CallbackTime::POST_RENDER:
      iterator = m_postRenderCallbacks.insert(m_postRenderCallbacks.end(), { p_callback, p_callOnce });
      break;
    }
    return iterator;
  }
  void RenderManager::RemoveRenderCallback(std::list<RenderCallback>::iterator p_index, CallbackTime p_time) {
    switch (p_time) {
    case CallbackTime::PRE_RENDER:
      m_preRenderCallbacks.erase(p_index);
      break;
    case CallbackTime::RENDER:
      m_renderCallbacks.erase(p_index);
      break;
    case CallbackTime::POST_RENDER:
      m_postRenderCallbacks.erase(p_index);
      break;
    }
  }

  void RenderManager::DrawFrame(FrameParams& p_prevFrame, FrameParams& p_currFrame) {
    p_currFrame.renderJob = JobManager::Instance().KickJob([&, m_window = m_window]() {
      JobManager::Instance().WaitForJobs({ p_currFrame.updateJob, p_prevFrame.renderJob });

      m_window->BeginFrame();

      //Call pre-render callbacks
      ExecuteCallbacks(m_preRenderCallbacks);

      //Call render callbacks
      ExecuteCallbacks(m_renderCallbacks);

      //Call post-render callbacks
      ExecuteCallbacks(m_postRenderCallbacks);

      m_window->EndFrame();
    });
  }

  ObjectHandle<Shader> RenderManager::GetShader(ShaderTypes p_type) {
    return m_shaders[p_type];
  }
}
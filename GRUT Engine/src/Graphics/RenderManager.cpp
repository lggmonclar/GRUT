#include "grutpch.h"
#include "RenderManager.h"
#include "Core/Jobs/JobManager.h"
#include "Core/Parallelism/FrameParams.h"

#include "Models/GLModel.h"
#include "Shaders/GLShader.h"
#include "Scene/Components/Rendering/Camera.h"
#include "Core/Config/Config.h"
#include <math.h>

namespace GRUT {
  RenderManager::~RenderManager() {
    delete[] m_singleFramePreRenderCallbacks;
    delete[] m_singleFrameRenderCallbacks;
    delete[] m_singleFramePostRenderCallbacks;
  }
  void RenderManager::ExecuteCallbacks(std::list<RenderCallback>& p_callbackList) {
    std::list<RenderCallback>::iterator i = p_callbackList.begin();
    while (i != p_callbackList.end()) {
      i->callback();
      if (i->executeOnce) {
        i = p_callbackList.erase(i);
      }
      else {
        i++;
      }
    }
  }

  void RenderManager::Initialize(std::shared_ptr<IWindow> p_window) {
    Instance().window = p_window;

    auto paramsCount = GET_CVAR(CVarInt, "frame_params_count");
    Instance().m_frameParamsCount = paramsCount;
    Instance().m_singleFramePreRenderCallbacks = new std::list<RenderCallback>[paramsCount];
    Instance().m_singleFrameRenderCallbacks = new std::list<RenderCallback>[paramsCount];
    Instance().m_singleFramePostRenderCallbacks = new std::list<RenderCallback>[paramsCount];

    if (true) {//TODO: Config for different apis
      Instance().LoadShaders<GLShader>();
    }
  }

  std::list<RenderCallback>::iterator RenderManager::RegisterRenderCallback(std::function<void()> p_callback, CallbackTime p_time, bool p_executeOnce) {
    std::list<RenderCallback>::iterator iterator;
    switch (p_time) {
    case CallbackTime::PRE_RENDER:
      iterator = m_preRenderCallbacks.insert(m_preRenderCallbacks.end(), { p_callback, p_executeOnce });
      break;
    case CallbackTime::RENDER:
      iterator = m_renderCallbacks.insert(m_renderCallbacks.end(), { p_callback, p_executeOnce });
      break;
    case CallbackTime::POST_RENDER:
      iterator = m_postRenderCallbacks.insert(m_postRenderCallbacks.end(), { p_callback, p_executeOnce });
      break;
    }
    return iterator;
  }

  void RenderManager::RegisterSingleFrameRenderCallback(std::function<void()> p_callback, CallbackTime p_time, short p_frameIdx) {
    std::list<RenderCallback>* callbackMap = &m_singleFrameRenderCallbacks[p_frameIdx];
    switch (p_time) {
    case CallbackTime::PRE_RENDER:
      callbackMap = &m_singleFramePreRenderCallbacks[p_frameIdx];
      break;
    case CallbackTime::RENDER:
      callbackMap = &m_singleFrameRenderCallbacks[p_frameIdx];
      break;
    case CallbackTime::POST_RENDER:
      callbackMap = &m_singleFramePostRenderCallbacks[p_frameIdx];
      break;
    }

    m_spinLock.Acquire();
    callbackMap->insert(callbackMap->end(), { p_callback });
    m_spinLock.Release();
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
    p_currFrame.renderJob = JobManager::Instance().KickJob([&, &window = window]() {
      JobManager::Instance().WaitForJobs({ p_currFrame.updateJob, p_prevFrame.renderJob });

      short prevIdx = (m_frameParamsCount + p_currFrame.index - 1) % m_frameParamsCount;
      m_singleFramePreRenderCallbacks[prevIdx].clear();
      m_singleFrameRenderCallbacks[prevIdx].clear();
      m_singleFramePostRenderCallbacks[prevIdx].clear();

      window->BeginFrame();

      //Call pre-render callbacks
      ExecuteCallbacks(m_preRenderCallbacks);
      ExecuteCallbacks(m_singleFramePreRenderCallbacks[p_currFrame.index]);

      //Call render callbacks
      ExecuteCallbacks(m_renderCallbacks);
      ExecuteCallbacks(m_singleFrameRenderCallbacks[p_currFrame.index]);

      //Call post-render callbacks
      ExecuteCallbacks(m_postRenderCallbacks);
      ExecuteCallbacks(m_singleFramePostRenderCallbacks[p_currFrame.index]);

      window->EndFrame();
    });
  }

  ObjectHandle<IShader> RenderManager::GetShader(ShaderTypes p_type) {
    return m_shaders[p_type];
  }
}
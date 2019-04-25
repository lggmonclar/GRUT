#pragma once
#include "Windows/IWindow.h"
#include "Core/Parallelism/SpinLock.h"
#include "Shaders/ShaderTypes.h"
#include "Core/Memory/MemoryManager.h"
#include "Core/Memory/ObjectHandle.h"
#include "Shaders/IShader.h"
#include "GUI/GUI.h"

namespace GRUT {
  struct FrameParams;
  
  enum class CallbackTime {
    PRE_RENDER,
    RENDER,
    POST_RENDER
  };

  struct RenderCallback {
    std::function<void()> callback;
    bool executeOnce = false;
  };

  class RenderManager {
  private:
    SpinLock m_spinLock;
    std::shared_ptr<IWindow> m_window;
    std::list<RenderCallback> m_preRenderCallbacks;
    std::list<RenderCallback> m_renderCallbacks;
    std::list<RenderCallback> m_postRenderCallbacks;

    std::list<RenderCallback> m_singleFramePreRenderCallbacks[Config::FRAME_PARAMS_COUNT];
    std::list<RenderCallback> m_singleFrameRenderCallbacks[Config::FRAME_PARAMS_COUNT];
    std::list<RenderCallback> m_singleFramePostRenderCallbacks[Config::FRAME_PARAMS_COUNT];

    GUI m_gui;

    std::map<ShaderTypes, ObjectHandle<IShader>> m_shaders;
    RenderManager() = default;
    ~RenderManager();
    void ExecuteCallbacks(std::list<RenderCallback> &p_callbackList);
    template <class T>
    void LoadShaders();
    int m_idx = 0;
  public:
    //inline std::shared_ptr<IWindow> GetWindow() { return m_window; }
    GRUT_API static RenderManager& Instance() {
      static RenderManager instance{};
      return instance;
    }
    static void Initialize(std::shared_ptr<IWindow> p_window);
    GRUT_API std::list<RenderCallback>::iterator RegisterRenderCallback(std::function<void()> p_callback, CallbackTime p_time = CallbackTime::RENDER, bool p_executeOnce = false);
    GRUT_API void RegisterSingleFrameRenderCallback(std::function<void()> p_callback, CallbackTime p_time, short p_frameIdx = -1);
    void RemoveRenderCallback(std::list<RenderCallback>::iterator p_index, CallbackTime p_time = CallbackTime::RENDER);
    void DrawFrame(FrameParams& p_prevFrame, FrameParams& p_currFrame);
    ObjectHandle<IShader> GetShader(ShaderTypes p_type);
  };
  template<class T>
  inline void RenderManager::LoadShaders() {
    auto diffuseShader = MemoryManager::Instance().AllocOnFreeList<T>();
    diffuseShader->LoadFragmentShader("../GRUT Engine/prefabs/shaders/diffuse_color.frag");
    diffuseShader->LoadVertexShader("../GRUT Engine/prefabs/shaders/diffuse_color.vert");
    m_shaders[ShaderTypes::DIFFUSE] = diffuseShader;

    auto blinnPhongShader = MemoryManager::Instance().AllocOnFreeList<T>();
    blinnPhongShader->LoadFragmentShader("../GRUT Engine/prefabs/shaders/blinn_phong.frag");
    blinnPhongShader->LoadVertexShader("../GRUT Engine/prefabs/shaders/blinn_phong.vert");
    m_shaders[ShaderTypes::PHONG] = blinnPhongShader;
  }
};
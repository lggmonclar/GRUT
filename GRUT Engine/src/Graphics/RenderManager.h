#pragma once
#include "Windows/IWindow.h"
#include "Core/Parallelism/SpinLock.h"
#include "Shaders/ShaderTypes.h"
#include "Core/Memory/MemoryManager.h"
#include "Core/Memory/ObjectHandle.h"
#include "Shaders/IShader.h"

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
            U8 m_frameParamsCount = 0;
            SpinLock m_spinLock;
            std::list<RenderCallback> m_preRenderCallbacks;
            std::list<RenderCallback> m_renderCallbacks;
            std::list<RenderCallback> m_postRenderCallbacks;

            std::list<RenderCallback>* m_singleFramePreRenderCallbacks = nullptr;
            std::list<RenderCallback>* m_singleFrameRenderCallbacks = nullptr;
            std::list<RenderCallback>* m_singleFramePostRenderCallbacks = nullptr;

            std::map<ShaderTypes, ObjectHandle<IShader>> m_shaders;
            RenderManager() = default;
            ~RenderManager();
            void ExecuteCallbacks(std::list<RenderCallback>& p_callbackList);
            template <class T>
            void LoadShaders();
            int m_idx = 0;

        public:
            static RenderManager& Instance() {
                static RenderManager instance{};
                return instance;
            }
            std::shared_ptr<IWindow> window;
            static void Initialize(std::shared_ptr<IWindow> p_window);
            std::list<RenderCallback>::iterator RegisterRenderCallback(std::function<void()> p_callback, CallbackTime p_time = CallbackTime::RENDER, bool p_executeOnce = false);
            void RegisterSingleFrameRenderCallback(std::function<void()> p_callback, CallbackTime p_time, short p_frameIdx = -1);
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
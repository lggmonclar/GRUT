#include "grutpch.h"
#include "Light.h"
#include "Scene/Scene.h"
#include "Graphics/RenderManager.h"
#include "Graphics/Shaders/GLShader.h"

namespace GRUT {
    void Light::SetType(LightType p_type) {
        m_spinlock.Acquire();
        auto currentScene = Scene::GetCurrent();

        //Remove from previous list
        switch (m_type) {
            case LightType::DIRECTIONAL:
                currentScene->directionalLights.erase(std::remove(currentScene->directionalLights.begin(), currentScene->directionalLights.end(), m_handle), currentScene->directionalLights.end());
                break;
            case LightType::POINT:
                currentScene->pointLights.erase(std::remove(currentScene->pointLights.begin(), currentScene->pointLights.end(), m_handle), currentScene->pointLights.end());
                break;
            case LightType::SPOTLIGHT:
                currentScene->spotLights.erase(std::remove(currentScene->spotLights.begin(), currentScene->spotLights.end(), m_handle), currentScene->spotLights.end());
                break;
        }

        m_type = p_type;

        //Add to appropriate list
        switch (m_type) {
            case LightType::DIRECTIONAL:
                currentScene->directionalLights.push_back(m_handle);
                break;
            case LightType::POINT:
                currentScene->pointLights.push_back(m_handle);
                break;
            case LightType::SPOTLIGHT:
                currentScene->spotLights.push_back(m_handle);
                break;
        }

        RenderManager::Instance().RegisterRenderCallback([=] {
            GLShader::UpdatePointLightsBuffer(currentScene->pointLights);
                                                         }, CallbackTime::PRE_RENDER, true);
        m_spinlock.Release();
    }
}

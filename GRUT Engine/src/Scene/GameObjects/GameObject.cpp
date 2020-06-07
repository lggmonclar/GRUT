#include "grutpch.h"
#include "DLLMacros.h"
#include "Scene/Scene.h"
#include "Scene/Components/Component.h"
#include "Core/Memory/MemoryManager.h"
#include "Core/Memory/ObjectHandle.h"
#include "GameObject.h"

namespace GRUT {
    void GameObject::Initialize(ObjectHandle<GameObject> p_handle) {
        LOG_INFO("INSTANTIATED GAMEOBJECT");
        p_handle->m_handle = p_handle;
        p_handle->transform = p_handle->AddComponent<Transform>();
    }
    void GameObject::ScheduleDestruction() {
        if (!m_isAlive) return;
        m_isAlive = false;
        LOG_INFO("SCHEDULED GAMEOBJECT FOR DELETION");
        scene->ScheduleGameObjectDestruction(m_handle);
    }
    void GameObject::DestroyComponents() {
        for (auto& [t, c] : m_components) {
            c->~Component();
            MemoryManager::Instance().FreeFromFreeList(&(*c));
        }
    }

    std::vector<ObjectHandle<Component>> GameObject::GetComponents() {
        std::vector<ObjectHandle<Component>> vector;
        for (auto& [key, value] : m_components) {
            vector.push_back(value);
        }
        return vector;
    }
    void GameObject::FixedUpdate(float p_deltaTime) {
        for (auto& [t, c] : m_components)
            c->FixedUpdate(p_deltaTime);
    }
    void GameObject::Update(float p_deltaTime) {
        for (auto& [t, c] : m_components)
            c->Update(p_deltaTime);
    }
}

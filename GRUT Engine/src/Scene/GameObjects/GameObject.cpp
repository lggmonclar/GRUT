#include "grutpch.h"
#include "DLLMacros.h"
#include "Scene/Components/Component.h"
#include "Scene/SceneManager.h"
#include "Core/Memory/MemoryManager.h"
#include "Core/Memory/ObjectHandle.h"
#include "GameObject.h"

namespace GRUT {
  ObjectHandle<GameObject> GameObject::Instantiate() {
    LOG_INFO("INSTANTIATED GAMEOBJECT");
    auto obj = SceneManager::Instance().CreateGameObject();
    obj->m_handle = obj;
    obj->transform = obj->AddComponent<Transform>();
    return obj;
  }
  void GameObject::Destroy() {
    if (!m_isAlive) return;
    LOG_INFO("DESTROYED GAMEOBJECT");
    SceneManager::Instance().DestroyGameObject(this);
    for (auto& [t, c] : m_components) {
      c->~Component();
      MemoryManager::Instance().FreeFromFreeList(&(*c));
    }
  }
  std::vector<ObjectHandle<Component>> GameObject::GetComponents() {
    std::vector<ObjectHandle<Component>> vector;
    for (auto &[key, value] : m_components) {
      vector.push_back(value);
    }
    return vector;
  }
  void GameObject::FixedUpdate(float p_deltaTime) {
    for (auto &[t, c] : m_components)
      c->FixedUpdate(p_deltaTime);
  }
  void GameObject::Update(float p_deltaTime) {
    for (auto &[t, c]: m_components)
      c->Update(p_deltaTime);
  }
}

#include "grutpch.h"
#include "DLLMacros.h"
#include "Components/Component.h"
#include "SceneManager.h"
#include "Core/Memory/MemoryManager.h"
#include "Core/Memory/ObjectHandle.h"
#include "GameObject.h"

namespace GRUT {
  ObjectHandle<GameObject> GameObject::Instantiate() {
    LOG_INFO("INSTANTIATED GAMEOBJECT");
    return SceneManager::Instance().CreateGameObject();
  }
  void GameObject::Destroy() {
    if (!m_isAlive) return;
    LOG_INFO("DESTROYED GAMEOBJECT");
    SceneManager::Instance().DestroyGameObject(this);
    for (auto &[t, c] : m_components)
      MemoryManager::Instance().FreeFromFreeList(&(*c));
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

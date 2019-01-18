#include "grutpch.h"
#include "DLLMacros.h"
#include "Component.h"
#include "SceneManager.h"
#include "Transform.h"
#include "Core/Memory/ObjectHandle.h"
#include "GameObject.h"

namespace GRUT {
  ObjectHandle<GameObject> GameObject::Instantiate() {
    LOG_INFO("INSTANTIATED GAMEOBJECT");
    return SceneManager::Instance().CreateGameObject();
  }
  void GameObject::Destroy() {
    LOG_INFO("DESTROYED GAMEOBJECT");
    SceneManager::Instance().DestroyGameObject(this);
  }
  void GameObject::FixedUpdate(float p_deltaTime) {
    for (auto &c : m_components)
      c->FixedUpdate(p_deltaTime);
  }
  void GameObject::Update(float p_deltaTime) {
    for (auto &c : m_components)
      c->Update(p_deltaTime);
  }
  GameObject::~GameObject() {}
}

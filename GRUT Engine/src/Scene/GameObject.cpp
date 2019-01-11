#include "grutpch.h"
#include "GameObject.h"
#include "SceneManager.h"

namespace GRUT {
  GameObject::GameObject() {
    m_transform = new Transform();
    m_components.push_back(m_transform);
  }
  GameObject* GameObject::Instantiate() {
    GRUT_INFO("INSTANTIATED GAMEOBJECT");
    return SceneManager::Instance().CreateGameObject();
  }
  GameObject::~GameObject() {
    for (auto &c : m_components)
      delete c;
  }
}

#include "grutpch.h"
#include "DLLMacros.h"
#include "Component.h"
#include "SceneManager.h"
#include "Transform.h"
#include "Core/Memory/ObjectHandle.h"
#include "GameObject.h"

namespace GRUT {
  ObjectHandle<GameObject> GameObject::Instantiate() {
    GRUT_INFO("INSTANTIATED GAMEOBJECT");
    return SceneManager::Instance().CreateGameObject();
  }
  void GameObject::Destroy() {
    GRUT_INFO("DESTROYED GAMEOBJECT");
    SceneManager::Instance().DestroyGameObject(this);
  }
  GameObject::~GameObject() {
  }
}

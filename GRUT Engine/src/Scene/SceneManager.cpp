#include "grutpch.h"
#include "Scene.h"
#include "Core/Memory/MemoryManager.h"
#include "Core/Memory/ObjectHandle.h"
#include "SceneManager.h"

namespace GRUT {
  void SceneManager::Initialize() {
    //TODO: Use custom allocator for the scene
    SceneManager::Instance().m_currentScene = new Scene();
  }

  ObjectHandle<GameObject> SceneManager::CreateGameObject() {
    auto gameObject = MemoryManager::Instance().AllocOnFreeList<GameObject>();
    m_currentScene->AddGameObject(gameObject);
    return gameObject;
  }

  void SceneManager::DestroyGameObject(GameObject* obj) {
    MemoryManager::Instance().FreeFromFreeList(obj);
  }

  SceneManager::~SceneManager() {
  }
}

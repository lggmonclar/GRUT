#include "grutpch.h"
#include "SceneManager.h"

namespace GRUT {
  void SceneManager::Initialize() {
    //TODO: Use custom allocator for the scene
    SceneManager::Instance().m_currentScene = new Scene();
  }

  GameObject* SceneManager::CreateGameObject() {
    //TODO: Use custom allocator for the game object
    auto gameObject = new GameObject();
    m_currentScene->AddGameObject(gameObject);
    return gameObject;
  }

  SceneManager::~SceneManager() {
  }
}

#include "grutpch.h"
#include "SceneManager.h"

namespace GRUT {
  void SceneManager::Initialize() {
    //TODO: Use custom allocator for the scene
    m_currentScene = new Scene();
  }
  SceneManager::~SceneManager() {
  }
}

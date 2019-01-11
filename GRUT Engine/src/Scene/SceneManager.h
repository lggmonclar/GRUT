#pragma once
#include "Scene.h"

namespace GRUT {
  class SceneManager {
  private:
    Scene *m_currentScene;
    SceneManager() = default;
    ~SceneManager();
  public:
    static SceneManager& Instance() {
      static SceneManager instance{};
      return instance;
    }
    static void Initialize();
    GameObject* CreateGameObject();
  };
}
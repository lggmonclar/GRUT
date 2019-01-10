#pragma once
#include "Scene.h"

namespace GRUT {
  class SceneManager {
  private:
    Scene *m_currentScene;
  public:
    SceneManager() = default;
    void Initialize();
    ~SceneManager();
  };
}
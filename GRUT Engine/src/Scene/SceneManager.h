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
    void FixedUpdate(float p_deltaTime);
    void Update(float p_deltaTime);
    ObjectHandle<GameObject> CreateGameObject();
    void DestroyGameObject(GameObject* obj);
  };
}
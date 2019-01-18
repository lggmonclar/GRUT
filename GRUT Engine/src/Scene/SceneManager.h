#pragma once
#include "Scene.h"

namespace GRUT {
  struct FrameParams;

  class SceneManager {
  private:
    Scene *m_currentScene;
    SceneManager() = default;
    ~SceneManager();
  public:
    int idx = 0;
    static SceneManager& Instance() {
      static SceneManager instance{};
      return instance;
    }
    static void Initialize();
    void FixedUpdate(float p_deltaTime);
    void Update(FrameParams& p_prevFrame, FrameParams& p_currFrame);
    ObjectHandle<GameObject> CreateGameObject();
    void DestroyGameObject(GameObject* obj);
  };
}
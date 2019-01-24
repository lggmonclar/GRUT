#pragma once
#include "Scene.h"

namespace GRUT {
  struct FrameParams;

  class SceneManager {
  private:
    int m_idx = 0;
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
    void Update(FrameParams& p_prevFrame, FrameParams& p_currFrame);
    ObjectHandle<GameObject> CreateGameObject();
    void DestroyGameObject(GameObject* obj);
  };
}
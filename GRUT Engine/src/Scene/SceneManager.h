#pragma once
#include "Scene.h"

namespace GRUT {
  struct FrameParams;

  class SceneManager {
    friend class Scene;
  private:
    ObjectHandle<Scene> m_currentScene;
    SceneManager() = default;
    ~SceneManager();
  public:
    short int frameIndex = 0;
    GRUT_API static SceneManager& Instance() {
      static SceneManager instance{};
      return instance;
    }
    static void Initialize();
    void FixedUpdate(float p_deltaTime);
    void Update(FrameParams& p_prevFrame, FrameParams& p_currFrame);
    ObjectHandle<GameObject> AllocateGameObject();
    void FreeGameObject(GameObject* obj);
  };
}
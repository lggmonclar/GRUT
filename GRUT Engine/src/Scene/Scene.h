#pragma once
#include <string>
#include "GameObject.h"

namespace GRUT {
  class Camera;
  class Scene {
    friend class FreeListAllocator;
  private:
    std::string m_name;
    std::vector<ObjectHandle<GameObject>> m_rootObjects;
    Scene() = default;
    ~Scene() = default;
  public:
    GRUT_API static ObjectHandle<Scene> GetCurrent();
    ObjectHandle<GameObject> mainCamera;
    void AddGameObject(ObjectHandle<GameObject> p_gameObject);
    void FixedUpdate(float p_deltaTime);
    void Update(FrameParams& p_prevFrame, FrameParams& p_currFrame);
  };
}
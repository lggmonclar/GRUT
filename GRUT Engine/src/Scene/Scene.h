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
    ObjectHandle<Camera> mainCamera;
    void AddGameObject(ObjectHandle<GameObject> p_gameObject);
    void FixedUpdate(float p_deltaTime);
    void Update(float p_deltaTime);
  };
}
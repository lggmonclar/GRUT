#pragma once
#include <string>
#include "GameObjects/GameObject.h"
#include "Components/Rendering/Light.h"

namespace GRUT {
  class Camera;
  class Scene {
    friend class FreeListAllocator;
    friend class SceneManager;
    friend class GameObject;
    friend class Light;
  private:
    std::string m_name;
    std::vector<ObjectHandle<GameObject>> m_rootObjects;
    std::vector<ObjectHandle<Light>> directionalLights;
    std::vector<ObjectHandle<Light>> pointLights;
    std::vector<ObjectHandle<Light>> spotLights;
    Scene() = default;
    ~Scene() = default;
    void FixedUpdate(float p_deltaTime);
    std::vector<std::weak_ptr<Job>> Update(FrameParams& p_prevFrame, FrameParams& p_currFrame);
    void AddGameObject(ObjectHandle<GameObject> p_gameObject);
    void UpdateLightSourceList(ObjectHandle<Light> p_handle, LightType p_type);
  public:
    ObjectHandle<GameObject> mainCamera;
    GRUT_API static ObjectHandle<Scene> GetCurrent();
  };
}
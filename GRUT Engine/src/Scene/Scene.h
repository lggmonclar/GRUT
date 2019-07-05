#pragma once
#include <string>
#include "GameObjects/GameObject.h"
#include "Components/Rendering/Light.h"

namespace GRUT {
  class Scene {
    friend class FreeListAllocator;
    friend class SceneManager;
    friend class GameObject;
    friend class Light;
  private:
    std::string m_name;
    ObjectHandle<Scene> m_handle;
    std::vector<ObjectHandle<GameObject>> m_rootObjects;
    std::vector<ObjectHandle<GameObject>> m_objectsScheduledForDeletion;
    std::vector<ObjectHandle<Light>> directionalLights;
    std::vector<ObjectHandle<Light>> pointLights;
    std::vector<ObjectHandle<Light>> spotLights;
    Scene() = default;
    ~Scene() = default;
    void FixedUpdate(float p_deltaTime);
    std::vector<std::weak_ptr<Job>> Update(FrameParams& p_prevFrame, FrameParams& p_currFrame);
    void ScheduleGameObjectDestruction(ObjectHandle<GameObject> p_gameObject);
    void DestroyScheduledGameObjects();
    void UpdateLightSourceList(ObjectHandle<Light> p_handle, LightType p_type);
  public:
    ObjectHandle<GameObject> mainCamera;
    static ObjectHandle<Scene> GetCurrent();
    ObjectHandle<GameObject> CreateGameObject();
  };
}
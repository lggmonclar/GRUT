#include "grutpch.h"
#include "Scene.h"
#include "Core/Jobs/JobManager.h"
#include "Scene/SceneManager.h"
#include "Core/Parallelism/FrameParams.h"
#include "Components/Rendering/Light.h"

namespace GRUT {
  ObjectHandle<Scene> Scene::GetCurrent() {
    return SceneManager::Instance().m_currentScene;
  }
  void Scene::AddGameObject(ObjectHandle<GameObject> p_gameObject) {
    m_rootObjects.push_back(p_gameObject);
  }
  void Scene::FixedUpdate(float p_deltaTime) {
    for (auto &obj : m_rootObjects) {
      obj->FixedUpdate(p_deltaTime);
    }
  }
  void Scene::Update(FrameParams& p_prevFrame, FrameParams& p_currFrame) {
    for (auto &obj : m_rootObjects) {
      JobManager::Instance().KickJob([&]() {
        obj->Update(p_currFrame.deltaTime);
      });
    }
  }
  void Scene::UpdateLightSourceList(ObjectHandle<Light> p_handle, LightType p_type) {
    
  }
  //Scene::~Scene() {
    //for (auto &obj : m_rootObjects)
    //  delete obj;
  //}
}
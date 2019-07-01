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
  ObjectHandle<GameObject> Scene::CreateGameObject() {
    auto gameObject = SceneManager::Instance().AllocateGameObject();
    gameObject->Initialize(gameObject);
    gameObject->scene = m_handle;
    m_rootObjects.push_back(gameObject);

    return gameObject;
  }
  void Scene::ScheduleGameObjectDestruction(ObjectHandle<GameObject> p_gameObject) {
    m_objectsScheduledForDeletion.push_back(p_gameObject);
  }

  void Scene::DestroyScheduledGameObjects() {
    for (auto& obj : m_objectsScheduledForDeletion) {
      m_rootObjects.erase(std::remove(m_rootObjects.begin(), m_rootObjects.end(), obj));
      obj->DestroyComponents();
      SceneManager::Instance().FreeGameObject(&(*obj));
    }
    m_objectsScheduledForDeletion.clear();
  }

  void Scene::FixedUpdate(float p_deltaTime) {
    for (auto &obj : m_rootObjects) {
      obj->FixedUpdate(p_deltaTime);
    }
  }
  std::vector<std::weak_ptr<Job>> Scene::Update(FrameParams& p_prevFrame, FrameParams& p_currFrame) {
    std::vector<std::weak_ptr<Job>> updateJobs;
    for (auto &obj : m_rootObjects) {
      updateJobs.push_back(JobManager::Instance().KickJob([&]() {
        obj->Update(p_currFrame.deltaTime);
      }));
    }
    return updateJobs;
  }
  void Scene::UpdateLightSourceList(ObjectHandle<Light> p_handle, LightType p_type) {
    
  }
}
#include "grutpch.h"
#include "Scene.h"
#include "Core/Jobs/JobManager.h"
#include "Core/Parallelism/FrameParams.h"

namespace GRUT {
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
        JobManager::Instance().WaitForJob(p_prevFrame.updateJob);
        obj->Update(p_currFrame.deltaTime);
      });
    }
  }
  //Scene::~Scene() {
    //for (auto &obj : m_rootObjects)
    //  delete obj;
  //}
}
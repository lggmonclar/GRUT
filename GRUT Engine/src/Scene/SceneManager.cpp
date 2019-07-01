#include "grutpch.h"
#include "Scene.h"
#include "Core/Parallelism/FrameParams.h"
#include "Core/Memory/MemoryManager.h"
#include "Core/Memory/ObjectHandle.h"
#include "SceneManager.h"
#include "Core/Jobs/JobManager.h"
#include "Components/Rendering/Camera.h"

namespace GRUT {
  void SceneManager::Initialize() {
    auto currScene = SceneManager::Instance().m_currentScene = MemoryManager::Instance().AllocOnFreeList<Scene>();
    auto obj = SceneManager::Instance().m_currentScene->CreateGameObject();
    obj->name = "Main Camera";
    obj->AddComponent<Camera>();
    currScene->mainCamera = obj;
    currScene->m_handle = currScene;
  }

  void SceneManager::FixedUpdate(float p_deltaTime) {
    m_currentScene->FixedUpdate(p_deltaTime);
  }

  void SceneManager::Update(FrameParams& p_prevFrame, FrameParams& p_currFrame) {
    p_currFrame.updateJob = JobManager::Instance().KickJob([&]() {
      JobManager::Instance().WaitForJobs({ p_currFrame.physicsJob, p_prevFrame.updateJob });
      frameIndex = p_currFrame.index;
      auto jobs = m_currentScene->Update(p_prevFrame, p_currFrame);
      JobManager::Instance().WaitForJobs(jobs);

      //Handle deferred object destructions
      Scene::GetCurrent()->DestroyScheduledGameObjects();
    });
  }

  ObjectHandle<GameObject> SceneManager::AllocateGameObject() {
    return MemoryManager::Instance().AllocOnFreeList<GameObject>();
  }

  void SceneManager::FreeGameObject(GameObject* obj) {
    MemoryManager::Instance().FreeFromFreeList(obj);
  }

  SceneManager::~SceneManager() {
  }
}

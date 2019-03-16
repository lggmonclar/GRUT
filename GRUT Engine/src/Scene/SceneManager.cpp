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
    SceneManager::Instance().m_currentScene = MemoryManager::Instance().AllocOnFreeList<Scene>();
    auto obj = GameObject::Instantiate();
    obj->name = "Main Camera";
    obj->AddComponent<Camera>();
    SceneManager::Instance().m_currentScene->mainCamera = obj;
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
    });
  }

  ObjectHandle<GameObject> SceneManager::CreateGameObject() {
    auto gameObject = MemoryManager::Instance().AllocOnFreeList<GameObject>();
    m_currentScene->AddGameObject(gameObject);
    gameObject->scene = m_currentScene;
    return gameObject;
  }

  void SceneManager::DestroyGameObject(GameObject* obj) {
    MemoryManager::Instance().FreeFromFreeList(obj);
  }

  SceneManager::~SceneManager() {
  }
}

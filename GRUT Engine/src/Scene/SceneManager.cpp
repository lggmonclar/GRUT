#include "grutpch.h"
#include "Scene.h"
#include "Core/Parallelism/FrameParams.h"
#include "Core/Memory/MemoryManager.h"
#include "Core/Memory/ObjectHandle.h"
#include "SceneManager.h"
#include "Core/Jobs/JobManager.h"

namespace GRUT {
  void SceneManager::Initialize() {
    //TODO: Use custom allocator for the scene
    SceneManager::Instance().m_currentScene = new Scene();
  }

  void SceneManager::FixedUpdate(float p_deltaTime) {
    m_currentScene->FixedUpdate(p_deltaTime);
  }

  void SceneManager::Update(FrameParams& p_prevFrame, FrameParams& p_currFrame) {
    p_currFrame.updateJob = JobManager::Instance().KickJob(Job([&](std::shared_ptr<Job> p) {
      p->WaitForJob(p_prevFrame.updateJob);
      GRUT_DEBUG("scene {0}", idx);
      m_currentScene->Update(p_currFrame.deltaTime);
      GRUT_DEBUG("scene {0}", idx++);
    }));
  }

  ObjectHandle<GameObject> SceneManager::CreateGameObject() {
    auto gameObject = MemoryManager::Instance().AllocOnFreeList<GameObject>();
    m_currentScene->AddGameObject(gameObject);
    return gameObject;
  }

  void SceneManager::DestroyGameObject(GameObject* obj) {
    MemoryManager::Instance().FreeFromFreeList(obj);
  }

  SceneManager::~SceneManager() {
  }
}

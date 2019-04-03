#include "grutpch.h"
#include "PhysicsManager.h"
#include "Core/Parallelism/FrameParams.h"
#include "Core/Jobs/JobManager.h"
#include "Scene/GameObjects/GameObject.h"
#include "GJK.h"

namespace GRUT {
  void PhysicsManager::Initialize() {
  }

  void PhysicsManager::Update(FrameParams & p_prevFrame, FrameParams & p_currFrame) {
    p_currFrame.physicsJob = JobManager::Instance().KickJob([&]() {
      JobManager::Instance().WaitForJob(p_prevFrame.physicsJob);

      auto collisionJobs = CheckCollisions();

      JobManager::Instance().WaitForJobs(collisionJobs);
    });
  }

  std::vector<ObjectHandle<Collider>>::iterator PhysicsManager::RegisterCollider(const ObjectHandle<Collider>& p_collider) {
    m_registeredColliders.push_back(p_collider);
    return m_registeredColliders.end();
  }

  void PhysicsManager::RemoveCollider(std::vector<ObjectHandle<Collider>>::iterator p_iterator) {
    m_registeredColliders.erase(p_iterator);
  }

  std::vector<std::weak_ptr<Job>> PhysicsManager::CheckCollisions() {
    std::vector<std::weak_ptr<Job>> collisionJobs;
    for (auto i = m_registeredColliders.begin(); i < m_registeredColliders.end(); i++) {
      for (auto j = i + 1; j < m_registeredColliders.end(); j++) {
        collisionJobs.push_back(JobManager::Instance().KickJob([=]() {
          auto &vec = m_activeCollisions[*i];
          auto it = std::find(vec.begin(), vec.end(), *j);

          if (GJK(*i, *j)) {
            if (it == vec.end()) {
              vec.push_back(*j);
              for (auto &c : (*i)->gameObject->GetComponents()) {
                c->OnCollisionEnter(*j);
              }
              for (auto &c : (*j)->gameObject->GetComponents()) {
                c->OnCollisionEnter(*i);
              }
            }
          }
          else {
            if (it != vec.end()) {
              vec.erase(it);
              for (auto &c : (*i)->gameObject->GetComponents()) {
                c->OnCollisionExit(*j);
              }
              for (auto &c : (*j)->gameObject->GetComponents()) {
                c->OnCollisionExit(*i);
              }
            }
          }
        }));
      }
    }
    return collisionJobs;
  }
}

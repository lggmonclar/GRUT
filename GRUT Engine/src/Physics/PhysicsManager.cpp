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

      CheckCollisions();
    });
  }

  std::vector<ObjectHandle<Collider>>::iterator PhysicsManager::RegisterCollider(const ObjectHandle<Collider>& p_collider) {
    m_registeredColliders.push_back(p_collider);
    return m_registeredColliders.end();
  }

  void PhysicsManager::RemoveCollider(std::vector<ObjectHandle<Collider>>::iterator p_iterator) {
    m_registeredColliders.erase(p_iterator);
  }

  void PhysicsManager::CheckCollisions() {
    for (auto i = m_registeredColliders.begin(); i < m_registeredColliders.end(); i++) {
      for (auto j = i + 1; j < m_registeredColliders.end(); j++) {
        if (GJK(*i, *j)) {
          //LOG_DEBUG("Collision detected!");
          for (auto &c : (*i)->gameObject->GetComponents()) {
            c->OnCollision(*j);
          }
          for (auto &c : (*j)->gameObject->GetComponents()) {
            c->OnCollision(*i);
          }
        }
      }
    }
  }
}

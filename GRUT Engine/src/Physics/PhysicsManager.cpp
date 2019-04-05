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
      JobManager::Instance().WaitForJobs({ p_prevFrame.memoryJob, p_prevFrame.physicsJob });

      CheckCollisions();
    });
  }

  void PhysicsManager::RegisterCollider(const ObjectHandle<Collider>& p_collider) {
    m_BVTree.AddCollider(p_collider);
  }

  void PhysicsManager::RemoveCollider(const ObjectHandle<Collider>& p_collider) {
    m_BVTree.RemoveCollider(p_collider);
  }

  void PhysicsManager::CheckCollisions() {
    m_BVTree.Update();

    auto lastFrameCollisions = m_activeCollisions;
    m_activeCollisions.clear();

    auto pairs = m_BVTree.GetCollisionPairs();
    for (auto &pair : pairs) {
        auto first = pair.first;
        auto second = pair.second;

        if (GJK(first, second)) {
          auto it = lastFrameCollisions.find(pair);

          if (it != lastFrameCollisions.end()) {
            // was colliding last frame
            lastFrameCollisions.erase(it);
          }
          else {
            // new collision
            for (auto &c : first->gameObject->GetComponents()) {
              c->OnCollisionEnter(second);
            }
            for (auto &c : second->gameObject->GetComponents()) {
              c->OnCollisionEnter(first);
            }
          }

          m_activeCollisions.insert(pair);
        }
    }

    for (const auto &pair : lastFrameCollisions) {
      auto first = pair.first;
      auto second = pair.second;

      for (auto &c : first->gameObject->GetComponents()) {
        c->OnCollisionExit(second);
      }
      for (auto &c : second->gameObject->GetComponents()) {
        c->OnCollisionExit(first);
      }
    }
  }
}

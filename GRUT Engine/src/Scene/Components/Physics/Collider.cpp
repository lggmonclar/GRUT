#include "grutpch.h"
#include "Collider.h"
#include "Physics/PhysicsManager.h"

namespace GRUT {
  void Collider::Initialize() {
    PhysicsManager::Instance().RegisterCollider(m_handle);
  }
  Collider::~Collider() {
    PhysicsManager::Instance().RemoveCollider(m_handle);
  }
}

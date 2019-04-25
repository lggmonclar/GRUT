#include "grutpch.h"
#include "ICollider.h"
#include "Physics/PhysicsManager.h"

namespace GRUT {
  void ICollider::Initialize() {
    PhysicsManager::Instance().RegisterCollider(m_handle);
  }
  ICollider::~ICollider() {
    PhysicsManager::Instance().RemoveCollider(m_handle);
  }
}

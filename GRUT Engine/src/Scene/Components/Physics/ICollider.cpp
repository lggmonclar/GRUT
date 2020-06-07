#include "grutpch.h"
#include "ICollider.h"
#include "Physics/PhysicsManager.h"
#include "Core/Config/Config.h"

namespace GRUT {
    float ICollider::s_fatFactor = -1.0f;

    void ICollider::Initialize() {
        if (s_fatFactor < 0) {
            s_fatFactor = GET_CVAR(CVarFloat, "collision_fat_factor");
        }
        PhysicsManager::Instance().RegisterCollider(m_handle);
    }
    ICollider::~ICollider() {
        PhysicsManager::Instance().RemoveCollider(m_handle);
    }
}

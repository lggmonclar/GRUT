#include "grutpch.h"
#include "BoxCollider.h"
#include "Scene/GameObjects/GameObject.h"
#include "Core/Debugging/Line.h"
#include "Core/Debugging/Box.h"
#include "Physics/AABB.h"

namespace GRUT {
  Vector<3> BoxCollider::Support(const Vector<3>& p_direction) {
    Vector<3> chosenVertex;
    float maxDist = -FLT_MAX;

    auto model = gameObject->transform->modelMatrix;

    for (int i = 0; i < 8; i++) {
      auto vert = m_vertices[i].ApplyMatrix4(gameObject->transform->modelMatrix);

      auto dist = vert.Dot(p_direction);
      if (dist > maxDist) {
        maxDist = dist;
        chosenVertex = vert;
      }
    }

    return chosenVertex;
  }

  void BoxCollider::Update(float p_deltaTime) {
    DEBUG_DRAW_BOX(gameObject->transform->GetPosition(), Vector<3>(1.0f, 1.0f, 1.0f), Vector<3>(0.0f, 0.0f, 0.0f), m_colliderColor);
  }

  void BoxCollider::OnCollisionEnter(ObjectHandle<ICollider> &p_other) {
    m_colliderColor = Vector<3>(1.0f, 0.0f, 0.2f);
  }

  void BoxCollider::OnCollisionExit(ObjectHandle<ICollider> &p_other) {
    m_colliderColor = Vector<3>(0.0f, 0.95f, 0.2f);
  }
  AABB BoxCollider::GetFatAABB() {
    AABB aabb = GetAABB();
    aabb.Expand(s_fatFactor);
    return aabb;
  }
  AABB BoxCollider::GetAABB() {
    auto transform = gameObject->transform;
    Vector<3> size = transform->GetScale();
    Vector<3> aabbSize;
    auto right = transform->GetRightVector();
    auto up = transform->GetUpVector();
    auto front = transform->GetFrontVector();

    for (int i = 0; i < 3; ++i) {
      aabbSize[i] = abs(right[i]) * size.x() + abs(up[i]) * size.y() + abs(front[i]) * size.z();
    }

    auto pos = transform->GetPosition();
    return AABB(pos, aabbSize);
  }
}

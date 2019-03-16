#include "grutpch.h"
#include "BoxCollider.h"
#include "Scene/GameObjects/GameObject.h"
#include "Core/Debugging/Line.h"
#include "Core/Debugging/Box.h"

namespace GRUT {
  Vector<3> boxColor = Vector<3>(0.0f, 0.95f, 0.2f);

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
    DEBUG_DRAW_BOX(gameObject->transform->GetPosition(), Vector<3>(1.0f, 1.0f, 1.0f), Vector<3>(0.0f, 0.0f, 0.0f), boxColor);
  }

  void BoxCollider::OnCollision(ObjectHandle<Collider> &p_other) {
    boxColor = Vector<3>(1.0f, 0.0f, 0.2f);
  }
}

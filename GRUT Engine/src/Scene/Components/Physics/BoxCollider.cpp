#include "grutpch.h"
#include "BoxCollider.h"
#include "Scene/GameObjects/GameObject.h"
#include "Core/Debugging/Line.h"

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
  }
}

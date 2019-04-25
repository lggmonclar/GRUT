#pragma once
#include "Core/Memory/ObjectHandle.h"
#include "Scene/Components/Physics/ICollider.h"

namespace GRUT {
  constexpr short MAX_ITERATIONS = 12;
  inline bool IsSameDirection(const Vector<3> &a, const Vector<3> &b) { return a.Dot(b) > 0; }

  bool GJK(const ObjectHandle<ICollider> &p_a, const ObjectHandle<ICollider> &p_b);
  bool CheckIntersection(Vector<3> p_simplexPoints[4], short &p_pointCount, Vector<3> &p_direction);
}
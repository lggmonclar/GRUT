#pragma once
#include <GRUTMath.h>
#include <vector>
#include "../Component.h"

namespace GRUT {
  using namespace GRUT::Math;
  class ICollider : public Component {
  protected:
    static float s_fatFactor;
  public:
    GRUT_API void Initialize() override;
    virtual Vector<3> Support(const Vector<3> &p_direction) = 0;
    virtual class AABB GetFatAABB() = 0;
    virtual class AABB GetAABB() = 0;
    GRUT_API ~ICollider();
  };
}
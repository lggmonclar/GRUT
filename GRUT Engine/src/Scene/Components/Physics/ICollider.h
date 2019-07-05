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
    void Initialize() override;
    virtual Vector3 Support(const Vector3 &p_direction) = 0;
    virtual class AABB GetFatAABB() = 0;
    virtual class AABB GetAABB() = 0;
    ~ICollider();
  };
}
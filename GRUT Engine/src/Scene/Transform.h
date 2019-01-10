#pragma once
#include "Component.h"
#include <GRUTMath.h>

namespace GRUT {
  class Transform : public Component {
  private:
  public:
    GRUT::Math::Vector<3> position;
    GRUT::Math::Vector<3> rotation;
    GRUT::Math::Vector<3> scale;
  };
}
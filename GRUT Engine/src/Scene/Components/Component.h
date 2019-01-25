#pragma once
#include "Core/GRUTAlias.h"

namespace GRUT {
  class Component {
  private:
  protected:
    Component() = default;
    ~Component() = default;
  public:
    void FixedUpdate(float p_deltaTime) {};
    void Update(float p_deltaTime) {};
  };
}

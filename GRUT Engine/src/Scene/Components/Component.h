#pragma once
#include "Core/GRUTAlias.h"
#include "Core/Memory/ObjectHandle.h"

namespace GRUT {
  class GameObject;
  class Component {
  private:
  protected:
    Component() = default;
    ~Component() = default;
  public:
    ObjectHandle<GameObject> gameObject;
    void FixedUpdate(float p_deltaTime) {};
    void Update(float p_deltaTime) {};
  };
}

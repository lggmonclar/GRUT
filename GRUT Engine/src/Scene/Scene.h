#pragma once
#include "GameObject.h"

namespace GRUT {
  class Scene {
  private:
    std::vector<GameObject*> m_rootObjects;
  public:
    Scene();
    ~Scene();
  };
}
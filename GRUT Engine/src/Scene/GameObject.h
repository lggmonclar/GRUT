#pragma once
#include <string>
#include <vector>
#include "Component.h"
#include "Transform.h"

namespace GRUT {
  class GameObject {
  private:
    std::string m_name;
    std::vector<Component*> m_components;
    std::vector<GameObject*> m_children;
    GameObject();
  public:
    Transform* m_transform;
    static GameObject Instantiate();
    ~GameObject();
  };
}
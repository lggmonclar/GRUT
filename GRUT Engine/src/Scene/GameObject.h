#pragma once
#include "DLLMacros.h"
#include <string>
#include <vector>
#include "Component.h"
#include "Transform.h"

namespace GRUT {
  class GameObject {
    friend class SceneManager;
  private:
    std::string m_name;
    std::vector<Component*> m_components;
    std::vector<GameObject*> m_children;
    GameObject();
  public:
    Transform* m_transform;
    static GRUT_API GameObject* Instantiate();
    ~GameObject();
  };
}
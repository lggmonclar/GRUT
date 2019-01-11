#pragma once
#include <string>
#include "GameObject.h"

namespace GRUT {
  class Scene {
  private:
    std::string m_name;
    std::vector<GameObject*> m_rootObjects;
  public:
    Scene();
    void AddGameObject(GameObject* p_gameObject);
    ~Scene();
  };
}
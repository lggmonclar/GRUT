#pragma once
#include <string>
#include "GameObject.h"

namespace GRUT {
  class Scene {
  private:
    std::string m_name;
    std::vector<ObjectHandle<GameObject>> m_rootObjects;
  public:
    Scene();
    void AddGameObject(ObjectHandle<GameObject> p_gameObject);
    ~Scene();
  };
}
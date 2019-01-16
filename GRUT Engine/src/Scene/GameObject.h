#pragma once
#include "Component.h"
#include "Transform.h"
#include "Core/Memory/ObjectHandle.h"

namespace GRUT {
  class GameObject {
    friend class FreeListAllocator;
  private:
    std::vector<ObjectHandle<Component>> m_components;
    std::vector<ObjectHandle<GameObject>> m_children;
  public:
    std::string m_name;
    Transform* m_transform;
    static GRUT_API ObjectHandle<GameObject> Instantiate();
    GRUT_API void Destroy();
    ~GameObject();
  };
}
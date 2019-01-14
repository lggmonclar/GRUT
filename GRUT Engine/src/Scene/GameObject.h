#pragma once
#include "Component.h"
#include "Transform.h"
#include "Core/Memory/ObjectHandle.h"

namespace GRUT {
  class GameObject {
    friend class FreeListAllocator;
  private:
    std::string m_name;
    std::vector<ObjectHandle<Component>> m_components;
    std::vector<ObjectHandle<GameObject>> m_children;
  public:
    Transform* m_transform;
    static GRUT_API ObjectHandle<GameObject> Instantiate();
    GRUT_API void Destroy();
    ~GameObject();
  };
}
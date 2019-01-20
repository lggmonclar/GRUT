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
    void UpdateSnapshot(int frame);
  public:
    std::string name;
    Transform transform;
    static GRUT_API ObjectHandle<GameObject> Instantiate();
    GRUT_API void Destroy();
    GRUT_API void FixedUpdate(float p_deltaTime);
    GRUT_API void Update(float p_deltaTime);
    ~GameObject();
  };
}
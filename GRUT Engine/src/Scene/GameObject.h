#pragma once
#include "DLLMacros.h"
#include <map>
#include "Components/Component.h"
#include "Components/Transform.h"
#include "Core/Memory/ObjectHandle.h"
#include "Core/Memory/MemoryManager.h"

namespace GRUT {
  class GameObject {
    friend class FreeListAllocator;
  private:
    std::vector<ObjectHandle<GameObject>> m_children;
    std::map<const char*, ObjectHandle<Component>> m_components;
    bool m_isAlive = true;
    ~GameObject() = default;
  public:
    std::string name;
    Transform transform;
    void FixedUpdate(float p_deltaTime);
    void Update(float p_deltaTime);
    GRUT_API static ObjectHandle<GameObject> Instantiate();
    GRUT_API void Destroy();
    template<class C>
    ObjectHandle<C> AddComponent();
    template<class C>
    ObjectHandle<C> GetComponent();
  };

  template<class C>
  ObjectHandle<C> GameObject::AddComponent() {
    auto component = MemoryManager::Instance().AllocOnFreeList<C>();
    m_components[typeid(C).name()] = component;
    return component;
  }
  template<class C>
  ObjectHandle<C> GameObject::GetComponent() {
    return m_components[typeid(C).name()];
  }
}
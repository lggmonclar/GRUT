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
    std::map<U16, ObjectHandle<Component>> m_components;
  public:
    std::string name;
    Transform transform;
    void FixedUpdate(float p_deltaTime);
    void Update(float p_deltaTime);
    GRUT_API static ObjectHandle<GameObject> Instantiate();
    GRUT_API void Destroy();
    ~GameObject();
    template<class C>
    void AddComponent();
    template<class C>
    ObjectHandle<C> GetComponent();
  };

  template<class C>
  void GameObject::AddComponent() {
    auto comp = MemoryManager::Instance().AllocOnFreeList<C>();
    m_components[GetType<C>()] = comp;
  }
  template<class C>
  ObjectHandle<C> GameObject::GetComponent() {
    return m_components[GetType<C>()];
  }
}
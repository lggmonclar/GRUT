#pragma once
#include "DLLMacros.h"
#include <map>
#include "Components/Component.h"
#include "Components/Transform.h"
#include "Core/Memory/ObjectHandle.h"
#include "Core/Memory/MemoryManager.h"

namespace GRUT {
  class Scene;
  class GameObject {
    friend class FreeListAllocator;
  private:
    bool m_isAlive = true;
    ObjectHandle<GameObject> m_handle;
    std::vector<ObjectHandle<GameObject>> m_children;
    std::map<std::string, ObjectHandle<Component>> m_components;
    GameObject() = default;
    ~GameObject() = default;
  public:
    std::string name;
    ObjectHandle<Transform> transform;
    ObjectHandle<Scene> scene;
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
    component->gameObject = m_handle;
    m_components[typeid(C).name()] = component;
    return component;
  }
  template<class C>
  ObjectHandle<C> GameObject::GetComponent() {
    return m_components[typeid(C).name()];
  }
}
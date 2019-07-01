#pragma once
#include "DLLMacros.h"
#include <map>
#include "Scene/Components/Component.h"
#include "Scene/Components/Transform.h"
#include "Core/Memory/ObjectHandle.h"
#include "Core/Memory/MemoryManager.h"

namespace GRUT {
  class Scene;
  class GameObject {
    friend class FreeListAllocator;
    friend class Scene;
  private:
    bool m_isAlive = true;
    ObjectHandle<GameObject> m_handle;
    std::vector<ObjectHandle<GameObject>> m_children;
    std::map<std::string, ObjectHandle<Component>> m_components;
    void Initialize(ObjectHandle<GameObject> p_handle);
    void DestroyComponents();
    GameObject() = default;
    ~GameObject() = default;
  public:
    std::string name;
    ObjectHandle<Transform> transform;
    ObjectHandle<Scene> scene;
    void FixedUpdate(float p_deltaTime);
    void Update(float p_deltaTime);
    GRUT_API void ScheduleDestruction();
    template<class C>
    ObjectHandle<C> AddComponent();
    template<class C>
    ObjectHandle<C> GetComponent();
    std::vector<ObjectHandle<Component>> GetComponents();
  };

  template<class C>
  ObjectHandle<C> GameObject::AddComponent() {
    auto component = MemoryManager::Instance().AllocOnFreeList<C>();
    component->gameObject = m_handle;
    component->SetHandle<C>(component);
    m_components[typeid(C).name()] = component;
    component->Initialize();
    return component;
  }
  template<class C>
  ObjectHandle<C> GameObject::GetComponent() {
    return m_components[typeid(C).name()];
  }
}
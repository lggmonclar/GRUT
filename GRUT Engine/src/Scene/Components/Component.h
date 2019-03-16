#pragma once
#include "Core/GRUTAlias.h"
#include "Core/Memory/ObjectHandle.h"

namespace GRUT {
  class GameObject;
  class Collider;

  class Component {
    friend class GameObject;
  private:
  protected:
    ObjectHandle<Component> m_handle;
    template <class C>
    void SetHandle(ObjectHandle<C> p_handle);
    Component() = default;
    ~Component() = default;
  public:
    ObjectHandle<GameObject> gameObject;
    GRUT_API virtual void Initialize() {}; //Called after m_handle is set
    GRUT_API virtual void FixedUpdate(float p_deltaTime) {};
    GRUT_API virtual void Update(float p_deltaTime) {};
    GRUT_API virtual void OnCollisionEnter(ObjectHandle<Collider> &p_other) {};
    GRUT_API virtual void OnCollisionExit(ObjectHandle<Collider> &p_other) {};
  };
  template<class C>
  inline void Component::SetHandle(ObjectHandle<C> p_handle) {
    m_handle = p_handle;
  }
}
#pragma once
#include "Core/GRUTAlias.h"
#include <functional>

namespace GRUT {
  class HandleEntry {
  public:
    U32 m_uid;
    void* m_ptr;
    bool m_isAvailable{ true };
  };

  template <class T>
  class ObjectHandle {
  private:
    U32 m_uid;
    std::function<HandleEntry()> m_handleGetter;
  public:
    ObjectHandle(std::function<HandleEntry()> p_handleGetter);
    T* operator->() const;
    T& operator*();
  };
  template<class T>
  inline ObjectHandle<T>::ObjectHandle(std::function<HandleEntry()> p_handleGetter) : m_handleGetter(p_handleGetter) {}

  template<class T>
  inline T * ObjectHandle<T>::operator->() const {
    return static_cast<T*>(m_handleGetter().m_ptr);
  }
  template<class T>
  inline T & ObjectHandle<T>::operator*() {
    return *(static_cast<T*>(m_handleGetter().m_ptr));
  }
}
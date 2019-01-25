#pragma once
#include "Core/GRUTAlias.h"
#include <functional>

namespace GRUT {
  class HandleEntry {
  public:
    void* m_ptr;
    bool m_isAvailable{ true };
  };

  template <class T>
  class ObjectHandle {
  private:
  public:
    std::function<HandleEntry()> m_handleGetter;

    //Covariance copy constructor
    template <typename Derived>
    ObjectHandle(const ObjectHandle<Derived>& derived,
      std::enable_if_t<std::is_base_of_v<T, Derived>>* = nullptr) {
      m_handleGetter = derived.m_handleGetter;
    }

    //Contravariance copy constructor
    template <typename Base>
    ObjectHandle(const ObjectHandle<Base>& base,
      std::enable_if_t<std::is_base_of_v<Base, T>>* = nullptr) {
      m_handleGetter = base.m_handleGetter;
    }

    ObjectHandle() = default;
    ObjectHandle(std::function<HandleEntry()> p_handleGetter);
    T* operator->() const;
    T& operator*();
  };
  template<class T>
  inline ObjectHandle<T>::ObjectHandle(std::function<HandleEntry()> p_handleGetter) : m_handleGetter(p_handleGetter) {}

  template<class T>
  inline T* ObjectHandle<T>::operator->() const {
    return static_cast<T*>(m_handleGetter().m_ptr);
  }
  template<class T>
  inline T& ObjectHandle<T>::operator*() {
    return *(static_cast<T*>(m_handleGetter().m_ptr));
  }
}
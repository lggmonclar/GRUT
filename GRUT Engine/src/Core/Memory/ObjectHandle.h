#pragma once
#include "Core/GRUTAlias.h"

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
    U32 m_index;
    U32 m_uid;
    HandleEntry* m_handleArr;
  public:
    ObjectHandle(U32 p_index, HandleEntry* p_handleArr);
    T* operator->() const;
    T& operator*();
  };
  template<class T>
  inline ObjectHandle<T>::ObjectHandle(U32 p_index, HandleEntry* p_handleArr) : m_index(p_index), m_handleArr(p_handleArr) {

  }
  template<class T>
  inline T * ObjectHandle<T>::operator->() const {
    return static_cast<T*>(m_handleArr[m_index].m_ptr);
  }
  template<class T>
  inline T & ObjectHandle<T>::operator*() {
    return *(static_cast<T*>(m_handleArr[m_index].m_ptr));
  }
}
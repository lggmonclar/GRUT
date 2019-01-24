#pragma once
#include "Core/GRUTAlias.h"

namespace GRUT {
  //class type_id_t {
  //  using sig = type_id_t();

  //  sig* id;
  //  type_id_t(sig* id) : id{ id } {}

  //public:
  //  template<typename T>
  //  friend type_id_t GetType();

  //  bool operator==(type_id_t o) const { return id == o.id; }
  //  bool operator!=(type_id_t o) const { return id != o.id; }
  //};

  class Component {
  private:
  protected:
    Component() = default;
    ~Component() = default;
  public:
    void FixedUpdate(float p_deltaTime) {};
    void Update(float p_deltaTime) {};
  };
  template<typename T>
  U16 GetType() {
    return 0;
    //return &type_id<T>();
  }
}

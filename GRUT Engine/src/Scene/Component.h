#pragma once

namespace GRUT {
  class Component {
  private:
  public:
    Component();
    ~Component();
    void FixedUpdate(float p_deltaTime) {};
    void Update(float p_deltaTime) {};
  };
}
#pragma once
#include <GRUT.h>

class Game : public GRUT::Root
{
public:
  Game() {
    InstanceTest();
  }

  void InstanceTest() {
    auto a = GRUT::GameObject::Instantiate();
    auto b = GRUT::GameObject::Instantiate();
    auto c = GRUT::GameObject::Instantiate();
    a->Destroy();
    b->Destroy();
    c->Destroy();
  }

  ~Game() {

  }
};
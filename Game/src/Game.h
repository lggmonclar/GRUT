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
    a->m_name = "obj-a";
    b->m_name = "obj-b"; 
    c->m_name = "obj-c";
    a->Destroy();
    b->Destroy();
    //c->Destroy();
  }

  ~Game() {

  }
};
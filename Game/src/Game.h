#pragma once
#include <GRUT.h>

class Game : public GRUT::Root
{
public:
  Game() {
    GRUT::GameObject::Instantiate();
  }

  ~Game() {

  }
};
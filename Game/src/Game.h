#pragma once
#include <GRUT.h>

class Game : public GRUT::Root
{
public:
  Game() {
    InstanceTest();
  }

  void InstanceTest() {
    auto cubeA = GRUT::GameObject::Instantiate();
    auto comp = cubeA->AddComponent<GRUT::RenderableComponent>();
    comp->SetModel("C:/Users/Lug/source/repos/GRUT Engine/GRUT Engine/test/models/box.obj");
    comp->SetShader("C:/Users/Lug/source/repos/GRUT Engine/GRUT Engine/test/shaders/diffuse_color.vert", "C:/Users/Lug/source/repos/GRUT Engine/GRUT Engine/test/shaders/diffuse_color.frag");
    //auto b = GRUT::GameObject::Instantiate();
    //auto c = GRUT::GameObject::Instantiate();

    //a->AddComponent<GRUT::RenderableComponent>();
    //auto comp = a->GetComponent<GRUT::RenderableComponent>();

    //a->Destroy();
    //b->Destroy();
    //c->Destroy();
  }

  ~Game() {

  }
};
#pragma once
#include <GRUT.h>
#include "Components/Test.h"

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
    cubeA->AddComponent<Test>();
    comp->SetShaderVec3("color", Vector<3>(1.0f, 0.0f, 0.0f));
  }

  ~Game() {

  }
};
#pragma once
#include <GRUT.h>
#include "Components/Test.h"
#include "Components/CameraController.h"

class Game : public GRUT::Root
{
public:
  Game() {
    InstanceTest();
  }

  void InstanceTest() {
    auto cubeA = GRUT::GameObject::Instantiate();
    auto comp = cubeA->AddComponent<GRUT::RenderableComponent>();
    comp->SetModel("../GRUT Engine/prefabs/models/sphere.obj");
    comp->SetShaderType(GRUT::ShaderTypes::PHONG);
    comp->SetShaderVec3("color", Vector<3>(0.0f, 0.0f, 0.4f));
    cubeA->transform->Translate(Vector<3>(0.0f, 0.0f, 5.0f));

    cubeA->AddComponent<Test>();
    //
    auto scene = GRUT::Scene::GetCurrent();
    scene->mainCamera->AddComponent<CameraController>();

    CreateLight(Vector<3>(3.0f, 2.0f, 0.0f));
    CreateLight(Vector<3>(3.0f, 2.0f, 10.0f));
    CreateLight(Vector<3>(-5.0f, 2.0f, 10.0f));
    CreateLight(Vector<3>(-5.0f, 2.0f, 0.0f));
  }

  void CreateLight(Vector<3> pos) {
    auto light = GRUT::GameObject::Instantiate();
    light->transform->SetScale(Vector<3>(0.2f, 0.2f, 0.2f));
    light->transform->Translate(pos);
    light->AddComponent<GRUT::Light>()->SetType(GRUT::LightType::POINT);
    auto renderableComp = light->AddComponent<RenderableComponent>();
    renderableComp->SetModel("../GRUT Engine/prefabs/models/sphere.obj");
    renderableComp->SetShaderType(GRUT::ShaderTypes::DIFFUSE);
    renderableComp->SetShaderVec3("color", Vector<3>(1.0f, 1.0f, 1.0f));
  }

  ~Game() {

  }
};
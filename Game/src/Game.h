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
    //auto cubeA = GRUT::GameObject::Instantiate();
    //auto comp = cubeA->AddComponent<GRUT::RenderableComponent>();
    //comp->SetModel("../GRUT Engine/prefabs/models/sphere.obj");
    //comp->SetShaderType(GRUT::ShaderTypes::PHONG);
    //comp->SetShaderVec3("color", Vector<3>(0.0f, 0.0f, 0.4f));
    //cubeA->transform->Translate(Vector<3>(0.0f, 0.0f, 5.0f));

    //cubeA->AddComponent<Test>();
    //
    auto scene = GRUT::Scene::GetCurrent();
    scene->mainCamera->AddComponent<CameraController>();

    int val = 5;
    for (int i = 0; i < val; i++) {
      for (int j = 0; j < val; j++) {
        for (int k = 0; k < val; k++) {
          CreateLight(Vector<3>(i*2.0f, j*2.0f, k*2.0f), Vector<3>(i / static_cast<float>(val), j / static_cast<float>(val), k / static_cast<float>(val)));
        }
      }
    }
  }

  void CreateLight(Vector<3> pos, Vector<3> color) {
    auto light = GRUT::GameObject::Instantiate();
    light->transform->SetScale(Vector<3>(0.2f, 0.2f, 0.2f));
    light->transform->Translate(pos);
    light->AddComponent<GRUT::Light>()->SetType(GRUT::LightType::POINT);
    auto renderableComp = light->AddComponent<RenderableComponent>();
    renderableComp->SetModel("../GRUT Engine/prefabs/models/sphere.obj");
    renderableComp->SetShaderType(GRUT::ShaderTypes::DIFFUSE);
    renderableComp->SetShaderVec3("color", color);
  }

  ~Game() {

  }
};
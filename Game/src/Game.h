#pragma once
#include <GRUT.h>
#include "Components/Test.h"
#include "Components/ColliderTest.h"
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
    scene->mainCamera->transform->Translate(Vector<3>(0.0f, 0.0f, -5.0f));

    //int val = 6;
    //for (int i = 0; i < val; i++) {
    //  for (int j = 0; j < val; j++) {
    //    for (int k = 0; k < val; k++) {
    //      CreateLight(Vector<3>(i*2.0f, j*2.0f, k*2.0f), Vector<3>(i / static_cast<float>(val), j / static_cast<float>(val), k / static_cast<float>(val)));
    //    }
    //  }
    //}

    //auto p_a = CreateCollideable(Vector<3>(5.0f, 0.0f, 0.0f), Vector<3>(1.0f, 1.0f, 0.0f), true);
    //auto p_b = CreateCollideable(Vector<3>(0.0f, 0.0f, 0.0f), Vector<3>(0.0f, 1.0f, 1.0f));

    int val = 3;
    for (int i = 0; i < val; i++) {
      for (int j = 0; j < val; j++) {
        for (int k = 0; k < val; k++) {
          CreateCollideable(Vector<3>(i*3.0f, j*3.0f, k*3.0f), Vector<3>(i / static_cast<float>(val), j / static_cast<float>(val), k / static_cast<float>(val)));
        }
      }
    }
    auto p_a = CreateCollideable(Vector<3>(5.0f, 0.0f, 0.0f), Vector<3>(1.0f, 1.0f, 0.0f), true);
  }


  void DrawPt(Vector<3> p_pos) {
    auto origin = GRUT::GameObject::Instantiate();
    origin->transform->SetScale(Vector<3>(0.02f, 0.02f, 0.02f));
    origin->transform->Translate(p_pos);
    auto renderableComp = origin->AddComponent<RenderableComponent>();
    renderableComp->SetModel("../GRUT Engine/prefabs/models/sphere.obj");
    renderableComp->SetShaderType(GRUT::ShaderTypes::DIFFUSE);
    renderableComp->SetShaderVec3("color", Vector<3>(1.0f, 0.1f, 0.3f));
  }

  void DrawOrigin() {
    auto origin = GRUT::GameObject::Instantiate();
    auto renderableComp = origin->AddComponent<RenderableComponent>();
    renderableComp->SetModel("../GRUT Engine/prefabs/models/sphere.obj");
    renderableComp->SetShaderType(GRUT::ShaderTypes::DIFFUSE);
    renderableComp->SetShaderVec3("color", Vector<3>(1.0f, 0.1f, 0.1f));
  }

  void CreateLight(Vector<3> pos, Vector<3> color) {
    auto light = GRUT::GameObject::Instantiate();
    light->transform->Translate(pos);
    light->AddComponent<GRUT::Light>()->SetType(GRUT::LightType::POINT);
    auto renderableComp = light->AddComponent<RenderableComponent>();
    renderableComp->SetModel("../GRUT Engine/prefabs/models/sphere.obj");
    renderableComp->SetShaderType(GRUT::ShaderTypes::DIFFUSE);
    renderableComp->SetShaderVec3("color", color);
    light->AddComponent<Test>();
  }

  GRUT::ObjectHandle<GRUT::ICollider> CreateCollideable(Vector<3> pos, Vector<3> color, bool p_addMovement = false) {
    auto obj = GRUT::GameObject::Instantiate();
    obj->transform->Translate(pos);
    auto comp = obj->AddComponent<GRUT::BoxCollider>();
    auto renderableComp = obj->AddComponent<RenderableComponent>();
    renderableComp->SetModel("../GRUT Engine/prefabs/models/sphere.obj");
    renderableComp->SetShaderType(GRUT::ShaderTypes::DIFFUSE);
    renderableComp->SetShaderVec3("color", color);
    
    if(p_addMovement)
      obj->AddComponent<ColliderTest>();

    return comp;
  }

  ~Game() {

  }
};
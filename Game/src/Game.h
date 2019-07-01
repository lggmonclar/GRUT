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
    //comp->SetShaderVec3("color", Vector3(0.0f, 0.0f, 0.4f));
    //cubeA->transform->Translate(Vector3(0.0f, 0.0f, 5.0f));

    //cubeA->AddComponent<Test>();
    //
    auto scene = GRUT::Scene::GetCurrent();
    scene->mainCamera->AddComponent<CameraController>();
    scene->mainCamera->transform->Translate(Vector3(0.0f, 0.0f, -5.0f));

    //int val = 6;
    //for (int i = 0; i < val; i++) {
    //  for (int j = 0; j < val; j++) {
    //    for (int k = 0; k < val; k++) {
    //      CreateLight(Vector3(i*2.0f, j*2.0f, k*2.0f), Vector3(i / static_cast<float>(val), j / static_cast<float>(val), k / static_cast<float>(val)));
    //    }
    //  }
    //}

    //auto p_a = CreateCollideable(Vector3(5.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), true);
    //auto p_b = CreateCollideable(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 1.0f));

    int val = 3;
    for (int i = 0; i < val; i++) {
      for (int j = 0; j < val; j++) {
        for (int k = 0; k < val; k++) {
          CreateCollideable(Vector3(i*3.0f, j*3.0f, k*3.0f), Vector3(i / static_cast<float>(val), j / static_cast<float>(val), k / static_cast<float>(val)));
        }
      }
    }
    auto p_a = CreateCollideable(Vector3(5.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), true);

    //p_a->gameObject->Destroy();

    auto coll = CreateCollideable(Vector3(10.0f, 10.0f, 10.0f), Vector3(1.0f, 1.0f, 1.0f));

    coll->gameObject->ScheduleDestruction();
  }


  void DrawPt(Vector3 p_pos) {
    auto origin = Scene::GetCurrent()->CreateGameObject();
    origin->transform->SetScale(Vector3(0.02f, 0.02f, 0.02f));
    origin->transform->Translate(p_pos);
    auto renderableComp = origin->AddComponent<RenderableComponent>();
    renderableComp->SetModel("../GRUT Engine/prefabs/models/sphere.obj");
    renderableComp->SetShaderType(GRUT::ShaderTypes::DIFFUSE);
    renderableComp->SetShaderVec3("color", Vector3(1.0f, 0.1f, 0.3f));
  }

  void DrawOrigin() {
    auto origin = Scene::GetCurrent()->CreateGameObject();
    auto renderableComp = origin->AddComponent<RenderableComponent>();
    renderableComp->SetModel("../GRUT Engine/prefabs/models/sphere.obj");
    renderableComp->SetShaderType(GRUT::ShaderTypes::DIFFUSE);
    renderableComp->SetShaderVec3("color", Vector3(1.0f, 0.1f, 0.1f));
  }

  void CreateLight(Vector3 pos, Vector3 color) {
    auto light = Scene::GetCurrent()->CreateGameObject();
    light->transform->Translate(pos);
    light->AddComponent<GRUT::Light>()->SetType(GRUT::LightType::POINT);
    auto renderableComp = light->AddComponent<RenderableComponent>();
    renderableComp->SetModel("../GRUT Engine/prefabs/models/sphere.obj");
    renderableComp->SetShaderType(GRUT::ShaderTypes::DIFFUSE);
    renderableComp->SetShaderVec3("color", color);
    light->AddComponent<Test>();
  }

  GRUT::ObjectHandle<GRUT::ICollider> CreateCollideable(Vector3 pos, Vector3 color, bool p_addMovement = false) {
    auto obj = Scene::GetCurrent()->CreateGameObject();
    obj->transform->Translate(pos);
    auto renderableComp = obj->AddComponent<RenderableComponent>();
    renderableComp->SetModel("../GRUT Engine/prefabs/models/sphere.obj");
    renderableComp->SetShaderType(GRUT::ShaderTypes::DIFFUSE);
    renderableComp->SetShaderVec3("color", color);
     
    GRUT::ObjectHandle<GRUT::ICollider> comp;
    if (p_addMovement) {
      obj->AddComponent<ColliderTest>();
    }
    //else {
    comp = obj->AddComponent<GRUT::BoxCollider>();
    //}

    return comp;
  }

  GRUT::ObjectHandle<GameObject> CreateRenderable(Vector3 pos, Vector3 color) {
    auto obj = Scene::GetCurrent()->CreateGameObject();
    obj->transform->Translate(pos);
    auto renderableComp = obj->AddComponent<RenderableComponent>();
    renderableComp->SetModel("../GRUT Engine/prefabs/models/sphere.obj");
    renderableComp->SetShaderType(GRUT::ShaderTypes::DIFFUSE);
    renderableComp->SetShaderVec3("color", color);

    return obj;
  }

  ~Game() {

  }
};
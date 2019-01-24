#include "grutpch.h"
#include "Scene.h"

namespace GRUT {
  Scene::Scene() {

  }
  void Scene::AddGameObject(ObjectHandle<GameObject> p_gameObject) {
    m_rootObjects.push_back(p_gameObject);
  }
  void Scene::FixedUpdate(float p_deltaTime) {
    for (auto &obj : m_rootObjects) {
      obj->FixedUpdate(p_deltaTime);
    }
  }
  void Scene::Update(float p_deltaTime) {
    for (auto &obj : m_rootObjects) {
      obj->Update(p_deltaTime);
    }
  }
  Scene::~Scene() {
    //for (auto &obj : m_rootObjects)
    //  delete obj;
  }
}
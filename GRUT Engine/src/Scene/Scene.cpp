#include "grutpch.h"
#include "Scene.h"

namespace GRUT {
  Scene::Scene() {

  }
  void Scene::AddGameObject(ObjectHandle<GameObject> p_gameObject) {
    m_rootObjects.push_back(p_gameObject);
  }
  Scene::~Scene() {
    //for (auto &obj : m_rootObjects)
    //  delete obj;
  }
}
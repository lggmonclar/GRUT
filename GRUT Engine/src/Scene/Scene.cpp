#include "grutpch.h"
#include "Scene.h"

namespace GRUT {
  Scene::Scene() {

  }
  Scene::~Scene() {
    for (auto &obj : m_rootObjects)
      delete obj;
  }
}
#include "grutpch.h"
#include "GameObject.h"

namespace GRUT {
  GameObject::GameObject() {
    //TODO: Use custom allocator
    m_transform = new Transform();
    m_components.push_back(m_transform);
  }
  GameObject GameObject::Instantiate() {
    //TODO: Use custom allocator to instantiate game object
    return GameObject();
  }
  GameObject::~GameObject() {
    for (auto &c : m_components)
      delete c;
  }
}

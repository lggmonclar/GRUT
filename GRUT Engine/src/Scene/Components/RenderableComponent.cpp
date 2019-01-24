#include "grutpch.h"
#include "RenderableComponent.h"
#include "Graphics/RenderManager.h"

namespace GRUT {
  RenderableComponent::RenderableComponent() : Component() {
    m_callbackId = RenderManager::Instance().RegisterRenderCallback([&] { Render(); });
  }
  RenderableComponent::~RenderableComponent() {
    RenderManager::Instance().RemoveRenderCallback(m_callbackId);
  }
  void RenderableComponent::Render() {
    LOG_INFO("Called render on renderable component");
  }
}

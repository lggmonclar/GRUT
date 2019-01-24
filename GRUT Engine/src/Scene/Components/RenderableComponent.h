#pragma once
#include "Component.h"
#include <list>
#include <functional>
#include "Graphics/Shaders/Shader.h"
#include "DLLMacros.h"

namespace GRUT {
  class RenderableComponent : public Component {
  private:
    std::list<std::function<void()>>::iterator m_callbackId;
    Shader *m_shader;
    void Render();
  public:
    GRUT_API RenderableComponent();
    ~RenderableComponent();
  };
}
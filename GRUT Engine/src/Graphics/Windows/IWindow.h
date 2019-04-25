#pragma once
#include <functional>

namespace GRUT {
  class IWindow {
  private:
  public:
    virtual void* GetNativeWindow() = 0;
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    virtual void PollEvents() = 0;
    virtual bool ShouldClose() = 0;
  };
};
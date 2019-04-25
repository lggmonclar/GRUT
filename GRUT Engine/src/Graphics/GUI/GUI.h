#pragma once

namespace GRUT {
  class GUI {
  private:
    bool m_hasInitialized = false;
    bool m_skipFrame = false;
    struct ImGuiContext* m_context = nullptr;
    void* m_nativeWindow = nullptr;
  public:
    void Initialize(void* p_nativeWindow, const char* p_version);
    void Destroy();

    void Render();
  };
}
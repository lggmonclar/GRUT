#pragma once
#include <imgui.h>
#ifndef IMGUI_IMPL_OPENGL_LOADER_GLAD
  #define IMGUI_IMPL_OPENGL_LOADER_GLAD
  #include <examples/imgui_impl_opengl3.h>
  #include <examples/imgui_impl_glfw.h>
#endif

using namespace GRUT;

class GUI {
private:
  bool m_hasInitialized = false;
  bool m_skipFrame = false;
  struct ImGuiContext* m_context = nullptr;
  void* m_nativeWindow = nullptr;
  void PrepareDockSpace();
  std::list<RenderCallback>::iterator m_renderCallbackId;
public:
  void Initialize(GRUT::RenderManager &p_renderManager);
  void Destroy();

  void Render();
};
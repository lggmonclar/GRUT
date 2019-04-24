#include "grutpch.h"
#include "GUI.h"
#include "Input/Input.h"

#include <imgui.cpp>
#include <imgui_draw.cpp>
#include <imgui_widgets.cpp>
#include <imgui_demo.cpp>
#ifdef IMGUI_IMPL_OPENGL_LOADER_GLAD
  #include <examples/imgui_impl_opengl3.cpp>
  #include <examples/imgui_impl_glfw.cpp>
#endif

namespace GRUT {
  void GUI::Initialize(void* p_nativeWindow, const char* p_version) {

    m_nativeWindow = p_nativeWindow;

    IMGUI_CHECKVERSION();
    m_context = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();

    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)m_nativeWindow, true);
    ImGui_ImplOpenGL3_Init(p_version);

    m_hasInitialized = true;
  }

  void GUI::Render() {
    ImGui::SetCurrentContext(m_context);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void GUI::Destroy() {
    if (m_hasInitialized) {
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();
      ImGui::DestroyContext();
    }
  }
}

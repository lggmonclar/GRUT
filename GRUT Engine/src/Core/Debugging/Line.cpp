#include "grutpch.h"
#include "Line.h"
#include "Scene/SceneManager.h"

namespace GRUT {
  bool Line::s_hasInitialized = false;
  GLShader Line::s_lineShader;
  unsigned int Line::s_VAO = 0;
  unsigned int Line::s_VBO = 0;

  void Line::Initialize() {
    s_lineShader.LoadVertexShader("../../GRUT Engine/GRUT Engine/prefabs/shaders/line.vert");
    s_lineShader.LoadFragmentShader("../../GRUT Engine/GRUT Engine/prefabs/shaders/line.frag");
    RenderManager::Instance().RegisterRenderCallback([=] {
      glGenBuffers(1, &s_VBO);
      glGenVertexArrays(1, &s_VAO);
    }, CallbackTime::PRE_RENDER, true);
  }
  void Line::Draw(Vector<3> p_startPos, Vector<3> p_endPos, Vector<3> p_color) {
    if (!s_hasInitialized) {
      Initialize();
      s_hasInitialized = true;
    }

    float vertices[] = {
      p_startPos.x(), p_startPos.y(), p_startPos.z(),
      p_endPos.x(), p_endPos.y(), p_endPos.z()
    };

    RenderManager::Instance().RegisterSingleFrameRenderCallback([=] {
      if (!s_VAO || !s_VBO) return;

      s_lineShader.Use();
      s_lineShader.SetVec3("lineColor", p_color);

      glBindVertexArray(s_VAO);
      glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);
      glDrawArrays(GL_LINES, 0, 2);
      glBindVertexArray(0);
    }, CallbackTime::RENDER, SceneManager::Instance().frameIndex);
  }
}

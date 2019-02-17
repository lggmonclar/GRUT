#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GRUTMath.h>
#include "Graphics/Shaders/GLShader.h"
#include "Graphics/RenderManager.h"

using namespace GRUT::Math;
namespace GRUT {
  class Line {
  private:
    static bool s_hasInitialized;
    static GLShader s_lineShader;
  public:
    static void Initialize() {
      RenderManager::Instance().RegisterRenderCallback([=] {
        s_lineShader.LoadVertexShader("../GRUT Engine/GRUT Engine/prefabs/shaders/line.vert");
        s_lineShader.LoadFragmentShader("../GRUT Engine/GRUT Engine/prefabs/shaders/line.frag");
      }, CallbackTime::PRE_RENDER, true);
    }

    static void Draw(Vector<3> p_startPos, Vector<3> p_endPos, Vector<3> p_color) {
      if (!s_hasInitialized) {
        s_hasInitialized = true;
        Initialize();
      }

      RenderManager::Instance().RegisterRenderCallback([=] {
        unsigned int VAO, VBO;
        float vertices[] = {
          p_startPos.x(), p_startPos.y(), p_startPos.z(),
          p_endPos.x(), p_endPos.y(), p_endPos.z()
        };
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        //position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        s_lineShader.Use();
        s_lineShader.SetVec3("lineColor", p_color);

        glDrawArrays(GL_LINES, 0, 2);
        glBindVertexArray(0);
      }, CallbackTime::RENDER, true);
    }
  };

  bool Line::s_hasInitialized = false;
  GLShader Line::s_lineShader;
}

// Log macros
#define DEBUG_DRAW_LINE(...) ::GRUT::Line::Draw(__VA_ARGS__)
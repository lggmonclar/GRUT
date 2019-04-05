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
    static unsigned int s_VBO;
    static unsigned int s_VAO;
  public:
    GRUT_API static void Initialize();
    GRUT_API static void Draw(Vector<3> p_startPos, Vector<3> p_endPos, Vector<3> p_color, bool p_drawNextFrame = false);
  };
}

#define DEBUG_DRAW_LINE(...) ::GRUT::Line::Draw(__VA_ARGS__)
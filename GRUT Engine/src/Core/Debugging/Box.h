#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GRUTMath.h>
#include "Graphics/Shaders/GLShader.h"
#include "Graphics/RenderManager.h"

using namespace GRUT::Math;
namespace GRUT {
  class Box {
  private:
    static bool s_hasInitialized;
    static unsigned int s_VBO, s_VAO, s_EBO;
    static ObjectHandle<GLShader> s_shader;
  public:
    GRUT_API static void Initialize();
    GRUT_API static void Draw(Vector3 p_center, Vector3 p_scale, Vector3 p_rotation, Vector3 p_color, bool p_drawThisFrame = false);
  };
}

#define DEBUG_DRAW_BOX(...) ::GRUT::Box::Draw(__VA_ARGS__)
#include "grutpch.h"
#include "Box.h"
#include "Scene/SceneManager.h"

namespace GRUT {
  bool Box::s_hasInitialized = false;
  ObjectHandle<GLShader> Box::s_shader;
  unsigned int Box::s_VAO = 0;
  unsigned int Box::s_VBO = 0;
  unsigned int Box::s_EBO = 0;

  void Box::Initialize() {
    s_shader = RenderManager::Instance().GetShader(ShaderTypes::DIFFUSE);
    RenderManager::Instance().RegisterRenderCallback([=] {
      float vertices[] = {
        0.0f, 1.0f, 0.0f, //Front top left
        1.0f, 1.0f, 0.0f, //Front top right
        0.0f, 0.0f, 0.0f, //Front bottom left
        1.0f, 0.0f, 0.0f, //Front bottom right
        0.0f, 1.0f, 1.0f, //Back top left
        1.0f, 1.0f, 1.0f, //Back top right
        0.0f, 0.0f, 1.0f, //Back bottom left
        1.0f, 0.0f, 1.0f  //Back bottom right
      };
      unsigned int indices[] = {
        0, 1,
        0, 2,
        2, 3,
        1, 3,

        0, 4,
        4, 5,
        1, 5,
        3, 7,

        4, 6,
        5, 7,
        6, 7,
        2, 6,
      };

      glGenBuffers(1, &s_VBO);
      glGenBuffers(1, &s_EBO);
      glGenVertexArrays(1, &s_VAO);

      glBindVertexArray(s_VAO);
      glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    }, CallbackTime::PRE_RENDER, true);
  }
  void Box::Draw(Vector3 p_center, Vector3 p_scale, Vector3 p_rotation, Vector3 p_color, bool p_drawNextFrame) {
    if (!s_hasInitialized) {
      Initialize();
      s_hasInitialized = true;
    }

    RenderManager::Instance().RegisterSingleFrameRenderCallback([=] {
      if (!s_VAO || !s_VBO || !s_EBO) return;

      Matrix4 model;
      Vector3 translation(p_center - p_scale / 2.0f);
      model.Translate(-p_scale / 2.0f);
      model.RotateX(p_rotation.x);
      model.RotateY(p_rotation.y);
      model.RotateZ(p_rotation.z);
      model.Translate(p_scale / 2.0f);

      model.Translate(translation);
      model.Scale(p_scale);

      s_shader->Use();
      s_shader->SetVec3("color", p_color);
      s_shader->SetMat4("model", model);

      glBindVertexArray(s_VAO);
      glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);

    }, CallbackTime::RENDER, SceneManager::Instance().frameIndex + p_drawNextFrame);
  }
}

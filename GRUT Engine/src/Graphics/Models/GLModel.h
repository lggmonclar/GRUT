#pragma once
#include "Model.h"
#include "GLMesh.h"
#include "GLTexture.h"
#include "Graphics/Shaders/GLShader.h"

namespace GRUT {
  class GLModel : public Model<GLMesh, GLTexture, GLShader> {};
}
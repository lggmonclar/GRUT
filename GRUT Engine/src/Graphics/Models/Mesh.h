#pragma once
#include <GRUTMath.h>
#include "Texture.h"
#include "Core/Memory/ObjectHandle.h"

class Shader;

namespace GRUT {
  struct Vertex {
    Math::Vector<3> position;
    Math::Vector<3> normal;
    Math::Vector<2> texCoords;
    Math::Vector<3> tangent;
    Math::Vector<3> bitangent;
  };

  class Mesh {
  protected:
    virtual void SetupMesh() = 0;
  public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<ObjectHandle<Texture>> textures;

    Mesh(std::vector<Vertex> p_vertices, std::vector<unsigned int> p_indices) : vertices(p_vertices), indices(p_indices) {}

    template <class TextureType>
    inline void AssignTextures(std::vector<ObjectHandle<TextureType>> p_textures) {
      textures.assign(p_textures.begin(), p_textures.end());
    }
  };
}
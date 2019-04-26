#pragma once
#include "IModel.h"
#include <GRUTMath.h>
#include "IMesh.h"
#include "Core/Memory/MemoryManager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Graphics/Shaders/GLShader.h"
#include "Core/Debugging/Logger.h"

namespace GRUT {
  template <class MeshType, class TextureType, class ShaderType>
  class Model : public IModel {
  private:
    void ProcessNode(aiNode *p_node, const aiScene *p_scene);
    MeshType ProcessMesh(aiMesh *p_mesh, const aiScene *p_scene);
    std::vector<ObjectHandle<TextureType>> LoadMaterialTextures(aiMaterial *p_mat, aiTextureType p_type, const std::string &p_typeName);
  public:
    void LoadModel(std::string const &p_path);
    std::vector<ObjectHandle<TextureType>> texturesLoaded;
    std::vector<MeshType> meshes;
    std::string directory;
    bool gammaCorrection = false;

    Model() = default;
    Model(std::string const &p_path, bool p_gamma = false);
    void Draw(ShaderType* p_shader);
  };

  template <class MeshType, class TextureType, class ShaderType>
  Model<MeshType, TextureType, ShaderType>::Model(std::string const & p_path, bool p_gamma) : gammaCorrection(p_gamma) {
    LoadModel(p_path);
  }

  template <class MeshType, class TextureType, class ShaderType>
  void Model<MeshType, TextureType, ShaderType>::Draw(ShaderType* p_shader) {
    for (unsigned int i = 0; i < meshes.size(); i++)
      meshes[i].Draw(p_shader);
  }

  template <class MeshType, class TextureType, class ShaderType>
  void Model<MeshType, TextureType, ShaderType>::LoadModel(std::string const & p_path) {
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(p_path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
      LOG_ERROR("Assimp Error:");
      LOG_ERROR(importer.GetErrorString());
      return;
    }
    // retrieve the p_directory p_path of the filepath
    directory = p_path.substr(0, p_path.find_last_of('/'));

    // process ASSIMP's root p_node recursively
    ProcessNode(scene->mRootNode, scene);
  }
  template <class MeshType, class TextureType, class ShaderType>
  void Model<MeshType, TextureType, ShaderType>::ProcessNode(aiNode * p_node, const aiScene * p_scene) {
    // process each p_mesh located at the current node
    for (unsigned int i = 0; i < p_node->mNumMeshes; i++) {
      // the node object only contains indices to index the actual objects in the p_scene. 
      // the p_scene contains all the data, node is just to keep stuff organized (like relations between nodes).
      aiMesh* mesh = p_scene->mMeshes[p_node->mMeshes[i]];
      meshes.push_back(ProcessMesh(mesh, p_scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < p_node->mNumChildren; i++) {
      ProcessNode(p_node->mChildren[i], p_scene);
    }
  }
  template <class MeshType, class TextureType, class ShaderType>
  MeshType Model<MeshType, TextureType, ShaderType>::ProcessMesh(aiMesh * p_mesh, const aiScene * p_scene) {
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<ObjectHandle<TextureType>> textures;

    // Walk through each of the p_mesh's vertices
    for (unsigned int i = 0; i < p_mesh->mNumVertices; i++) {
      Vertex vertex;
      // positions
      vertex.position[0] = p_mesh->mVertices[i].x;
      vertex.position[1] = p_mesh->mVertices[i].y;
      vertex.position[2] = p_mesh->mVertices[i].z;

      // normals
      if (p_mesh->mNormals) {
        vertex.normal[0] = p_mesh->mNormals[i].x;
        vertex.normal[1] = p_mesh->mNormals[i].y;
        vertex.normal[2] = p_mesh->mNormals[i].z;
      }

      // texture coordinates
      if (p_mesh->mTextureCoords[0]) {
        // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
        // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
        vertex.texCoords[0] = p_mesh->mTextureCoords[0][i].x;
        vertex.texCoords[1] = p_mesh->mTextureCoords[0][i].y;
      }

      // tangent
      if (p_mesh->mTangents) {
        vertex.tangent[0] = p_mesh->mTangents[i].x;
        vertex.tangent[1] = p_mesh->mTangents[i].y;
        vertex.tangent[2] = p_mesh->mTangents[i].z;
      }

      // bitangent
      if (p_mesh->mBitangents) {
        vertex.bitangent[0] = p_mesh->mBitangents[i].x;
        vertex.bitangent[1] = p_mesh->mBitangents[i].y;
        vertex.bitangent[2] = p_mesh->mBitangents[i].z;
      }

      vertices.push_back(vertex);
    }
    // now wak through each of the p_mesh's faces (a face is a p_mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < p_mesh->mNumFaces; i++) {
      aiFace face = p_mesh->mFaces[i];
      // retrieve all indices of the face and store them in the indices vector
      for (unsigned int j = 0; j < face.mNumIndices; j++)
        indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = p_scene->mMaterials[p_mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    auto diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    auto specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    auto normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    auto heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted p_mesh data
    MeshType mesh(vertices, indices);
    mesh.AssignTextures(textures);
    return mesh;
  }

  template <class MeshType, class TextureType, class ShaderType>
  std::vector<ObjectHandle<TextureType>> Model<MeshType, TextureType, ShaderType>::LoadMaterialTextures(aiMaterial * p_mat, aiTextureType p_type, const std::string &p_typeName) {
    std::vector<ObjectHandle<TextureType>> textures;
    for (unsigned int i = 0; i < p_mat->GetTextureCount(p_type); i++) {
      aiString str;
      p_mat->GetTexture(p_type, i, &str);
      // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
      bool skip = false;
      for (unsigned int j = 0; j < texturesLoaded.size(); j++) {
        if (std::strcmp(texturesLoaded[j]->path.data(), str.C_Str()) == 0) {
          textures.push_back(texturesLoaded[j]);
          skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
          break;
        }
      }
      if (!skip) {   // if texture hasn't been loaded already, load it
        ObjectHandle<TextureType> texture = MemoryManager::Instance().AllocOnFreeList<TextureType>(str.C_Str(), this->directory, p_typeName);
        textures.push_back(texture);
        texturesLoaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
      }
    }
    return textures;
  }
}
#include "grutpch.h"
#include "GLTexture.h"
#include <stb_image.h>

namespace GRUT {
  GLTexture::GLTexture(const char *p_path, const std::string &p_directory, const std::string &p_type) {
    path = p_path;
    type = p_type;
    std::string filename = std::string(p_path);
    filename = p_directory + '/' + filename;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

    if (data) {
      InitTexture(data);
    }
    else {
      LOG_ERROR("Texture failed to load at path: {0}", p_path);
    }

    stbi_image_free(data);
  }

  void GLTexture::InitTexture(unsigned char * p_data) {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, p_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }
}

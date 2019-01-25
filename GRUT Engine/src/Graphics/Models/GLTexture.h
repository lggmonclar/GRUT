#pragma once
#include "Texture.h"

namespace GRUT {
  class GLTexture : public Texture {
  protected:
    void InitTexture(unsigned char* p_data) override;
  public:
    GLTexture(const char *p_path, const std::string &p_directory, const std::string &p_type);
  };
}
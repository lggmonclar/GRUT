#pragma once
#include <string>

namespace GRUT {
  class Texture {
  protected:
    int width, height, nrComponents;
    virtual void InitTexture(unsigned char* p_data) = 0;
  public:
    unsigned int id;
    std::string type;
    std::string path;
  };
}
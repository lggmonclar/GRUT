#include "grutpch.h"
#include "FileSystem.h"

namespace GRUT {
  std::string FileSystem::LoadFileContents(const char* path) {
    std::ifstream fileStream;
    std::stringstream stringStream;

    fileStream.open(path);
    if (fileStream.bad()) {
      LOG_ERROR("Failed to open file");
      LOG_ERROR("File was {0}", path);
      return "";
    }
    stringStream << fileStream.rdbuf();
    fileStream.close();

    return stringStream.str();
  }
}

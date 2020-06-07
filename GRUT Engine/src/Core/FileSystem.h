#pragma once
#include <string>

namespace GRUT {
    class FileSystem {
        public:
        static std::string LoadFileContents(const char* path);
    };
}
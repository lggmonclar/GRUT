#pragma once
#include "ITexture.h"

namespace GRUT {
    class GLTexture : public ITexture {
        protected:
            void InitTexture(unsigned char* p_data) override;

        public:
            GLTexture(const char* p_path, const std::string& p_directory, const std::string& p_type);
    };
}
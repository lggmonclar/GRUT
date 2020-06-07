#pragma once
#include "IMesh.h"
#include <vector>

class GLShader;

namespace GRUT {
    class GLMesh : public IMesh {
        private:
            unsigned int m_VBO, m_EBO, m_VAO;

        protected:
            void SetupMesh() override;

        public:
            GLMesh(std::vector<Vertex> p_vertices, std::vector<unsigned int> p_indices);
            void Draw(GLShader* p_shader);
    };
}
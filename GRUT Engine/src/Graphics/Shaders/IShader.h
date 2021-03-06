#pragma once
#include <GRUTMath.h>
#include <string>

namespace GRUT {
    class IShader {
        private:
            protected:
            virtual bool CompileVertexShader(const char* p_vertexCode) = 0;
            virtual bool CompileFragmentShader(const char* p_fragmentCode) = 0;
            virtual bool CheckCompileErrors(unsigned int shader, const std::string& type) = 0;

        public:
            IShader() = default;
            void LoadVertexShader(const char* path);
            void LoadFragmentShader(const char* path);

            virtual void SetBool(const std::string& name, bool value) const = 0;
            virtual void SetInt(const std::string& name, int value) const = 0;
            virtual void SetFloat(const std::string& name, float value) const = 0;
            virtual void SetVec2(const std::string& name, const Math::Vector2& v2) const = 0;
            virtual void SetVec2(const std::string& name, float x, float y) const = 0;
            virtual void SetVec3(const std::string& name, const Math::Vector3& v3) const = 0;
            virtual void SetVec3(const std::string& name, float x, float y, float z) const = 0;
            virtual void SetVec4(const std::string& name, const Math::Vector4& v4) const = 0;
            virtual void SetVec4(const std::string& name, float x, float y, float z, float w) const = 0;
            virtual void SetMat4(const std::string& name, const Math::Matrix4& m4) const = 0;
    };
}
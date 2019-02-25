#version 430 core
layout (location = 0) in vec3 aPos;

layout (std140, binding = 0) uniform Matrices {
    mat4 view;
    mat4 projection;
};

void main() {
    gl_Position = projection * view * vec4(aPos, 1.0);
}
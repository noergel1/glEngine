#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 6) in mat4 aInstanceMatrix;

layout (std140, binding = 0) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

void main()
{
    gl_Position =  projection * view * aInstanceMatrix * vec4(aPos, 1.0);
}  
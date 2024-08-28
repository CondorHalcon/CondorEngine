#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 normal;

//uniforms
layout (location = 0) uniform mat4 proj; // clip space
layout (location = 1) uniform mat4 view; // view space
layout (location = 2) uniform mat4 model; // world space i.e. transform

out vec4 vPos;
out vec4 vCol;
out vec2 vUV;
out vec3 vNorm;

void main()
{
    vPos = model * position;
    vCol = color;
    vUV = uv;
    vNorm = mat3(model) * normal;

    // model view projection matrix
    gl_Position = proj * view * model * position;
}
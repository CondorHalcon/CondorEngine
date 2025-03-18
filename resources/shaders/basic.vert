#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 uv;

//uniforms
layout (location = 0) uniform mat4 proj; // clip space
layout (location = 1) uniform mat4 view; // view space
layout (location = 2) uniform mat4 model; // world space i.e. transform

out vec4 vPos;
out vec4 vCol;
out vec2 vUV;

void main()
{
    // # Vertex Output
    // -----------------
    vPos = position;
    vCol = color;
    vUV = uv;

    // model view projection matrix
    gl_Position = proj * view * model * position;
}
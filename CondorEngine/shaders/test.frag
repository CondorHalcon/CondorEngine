#version 430 core

#define COUNT 2

in vec4 vPos;
in vec4 vCol;
in vec2 vUV;
in vec3 vNorm;

out vec4 fragColor;

layout (location = 3) uniform vec3 colors[COUNT];

void main() {
    fragColor = vec4(colors[1], 1);
}
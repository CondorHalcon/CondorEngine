#version 430 core

in vec4 vPos;
in vec4 vCol;
in vec2 vUV;

out vec4 fragColor;

void main() 
{
    fragColor = vec4(vUV.x, vUV.y, 0, 1);
}
#version 430 core

in vec4 vPos;
in vec4 vCol;
in vec2 vUV;
in vec3 vNorm;

out vec4 fragColor;

void main() 
{
    fragColor = vec4(abs(vNorm.x),abs(vNorm.y),abs(vNorm.z), 1);
}
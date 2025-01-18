#version 430 core

in vec4 vPos;
in vec4 vCol;
in vec2 vUV;

out vec4 fragColor;

layout (location = 3) uniform sampler2D mainTex;

void main() 
{
    vec4 texCol = texture(mainTex, vUV);
    fragColor = (texCol != vec4(0,0,0,1) ? texCol : vec4(1,1,1,1)) * vCol;
}
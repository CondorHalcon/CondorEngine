#version 430 core

in vec4 vPos;
in vec4 vCol;
in vec2 vUV;
in vec3 vNorm;

out vec4 fragColor;

void main() 
{
    // # Normal Color
    vec3 norm = normalize(vNorm);

    norm += 1;
    norm *= .5;

    // # Fragment Output
    // -----------------
    fragColor = vec4(norm, 1);
}
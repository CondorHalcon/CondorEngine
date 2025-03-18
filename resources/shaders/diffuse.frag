#version 430 core

in vec4 vPos;
in vec4 vCol;
in vec2 vUV;
in vec3 vNorm;

out vec4 fragColor;

layout (location = 3) uniform vec3 ambient = vec3(0.5,0.5,0.5);
layout (location = 4) uniform vec3 dirLightColor = vec3(1.0,1.0,1.0);
layout (location = 5) uniform vec3 dirLightDirection = vec3(0.5,0.5,0.0);
layout (location = 6) uniform sampler2D mainTex;

void main() 
{
    vec4 baseLit = vec4(ambient.rgb, 1.0);

    vec3 n = normalize(vNorm);
    vec3 L = normalize(dirLightDirection);

    // lambertTerm
    float lambert = max(0, dot(n, -L));
    // remapped to vec4 for the maths
    vec4 lum = vec4(lambert, lambert, lambert, 1.0);

    vec4 litColor = vec4(dirLightColor, 1.0);

    // texture and vertex color
    vec4 color = texture(mainTex, vUV);
    vec4 texCol = (color != vec4(0,0,0,1) ? color : vec4(1,1,1,1)) * vCol * litColor;

    fragColor = texCol * lum + texCol * baseLit;
}
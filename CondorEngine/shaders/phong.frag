#version 430 core

in vec4 vPos;
in vec4 vCol;
in vec2 vUV;
in vec3 vNorm;

out vec4 fragColor;

layout (location = 3) uniform vec3 ambient;
layout (location = 4) uniform vec3 dirLightDirection;
layout (location = 5) uniform vec3 dirLightColor;
layout (location = 6) uniform sampler2D mainTex;
layout (location = 7) uniform vec3 cameraPos;

void main() 
{
    vec4 baseLit = vec4(ambient.rgb, 1.0);

    vec3 n = normalize(vNorm);
    vec3 L = normalize(dirLightDirection);

    // lambertTerm
    float lambert = max(0, dot(n, -L));
    // remapped to vec4 for the maths
    vec4 lum = vec4(lambert, lambert, lambert, 1.0);

    vec3 V = normalize(cameraPos - vPos.xyz);
    vec3 R = reflect(L, n);

    // calculate specular power
    float specularPower = 64.0;
    float specularTermination = pow(max(0, dot(R,V)), specularPower);
    // set w to 0 because we will be adding the vec4 to another vec4
    vec4 specular = vec4(dirLightColor * specularTermination, 0);

    vec4 litColor = vec4(dirLightColor, 1.0);

    // texture and vertex color
    vec4 color = texture(mainTex, vUV);
    vec4 texCol = (color != vec4(0,0,0,1) ? color : vec4(1,1,1,1)) * vCol * litColor;

    fragColor = texCol * lum + texCol * baseLit + specular;
}
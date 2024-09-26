#version 430 core

#define MAX_LIGHTS 2

in vec4 vPos;
in vec4 vCol;
in vec2 vUV;
in vec3 vNorm;

out vec4 fragColor;

layout (location = 3) uniform vec3 ambient;
layout (location = 4) uniform vec3 cameraPos;
layout (location = 5) uniform sampler2D mainTex;
uniform vec3 lightColor[MAX_LIGHTS];
uniform vec3 lightDirection[MAX_LIGHTS];

void main() 
{
    vec4 baseLit = vec4(ambient.rgb, 1.0);

    vec4 lum = vec4(0, 0, 0, 1.0);
    vec4 specular = vec4(0, 0, 0, 0);
    vec4 litColor = vec4(0, 0, 0, 1.0);

    float specularPower = 64.0;

    for (int i = 0; i < MAX_LIGHTS; i++) {
        vec3 n = normalize(vNorm);
        vec3 L = normalize(lightDirection[i]);

        // lambertTerm
        float lambert = max(0, dot(n, -L));
        // remapped to vec4 for the maths
        lum += vec4(lambert, lambert, lambert, 0);

        vec3 V = normalize(cameraPos - vPos.xyz);
        vec3 R = reflect(L, n);

        // calculate specular power
        float specularTermination = pow(max(0, dot(R,V)), specularPower);
        // set w to 0 because we will be adding the vec4 to another vec4
        specular += vec4(lightColor[i] * specularTermination, 0);

        litColor += vec4(lightColor[i], 0);
    }

    // texture and vertex color
    vec4 color = texture(mainTex, vUV);
    vec4 texCol = (color != vec4(0,0,0,1) ? color : vec4(1,1,1,1)) * vCol * litColor;

    vec4 col = (texCol * lum) + (texCol * baseLit) + specular;
    fragColor = vec4(col.rgb, 1);
}
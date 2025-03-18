#version 430 core

struct Material {
    sampler2D texture;
    vec3 tint;
};

in vec4 vPos;
in vec4 vCol;
in vec2 vUV;
in vec3 vNorm;

out vec4 fragColor;

layout (location = 3) uniform vec3 ambientColor;
layout (location = 4) uniform vec3 dirLightColor;
layout (location = 5) uniform vec3 dirLightDirection;

uniform Material material;

void main() 
{
    // # Ambient Lighting
    // ------------------
    vec3 ambient = ambientColor.rgb;

    // # Diffuse Lighting
    // ------------------
    vec3 norm = normalize(vNorm);
    vec3 lightDir = normalize(dirLightDirection);

    float diff = max(0., dot(norm, -lightDir));
    vec3 diffuse = diff * dirLightColor;

    // # Texture Color
    // ---------------
    vec3 color = texture(material.texture, vUV).rgb * material.tint;

    // # Fragment Output
    // -----------------
    vec3 result = (ambient + diffuse) * color;
    fragColor = vec4(result, 1.);
}
#version 430 core

struct Material {
    sampler2D texture;
    vec3 tint;
    float specular;
    float smoothness;
};

in vec4 vPos;
in vec4 vCol;
in vec2 vUV;
in vec3 vNorm;

out vec4 fragColor;

layout (location = 3) uniform vec3 ambientColor;
layout (location = 4) uniform vec3 dirLightColor;
layout (location = 5) uniform vec3 dirLightDirection;
layout (location = 6) uniform vec3 cameraPos;

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

    float diff = max(0, dot(norm, -lightDir));
    vec3 diffuse = diff * dirLightColor;

    // # Specular Lighting
    // -------------------
    vec3 viewDir = normalize(cameraPos - vPos.xyz);
    vec3 reflectDir = reflect(lightDir, norm);

    float specularTermination = pow(max(0.0, dot(reflectDir, viewDir)), 64. * material.smoothness);
    vec3 specular = material.specular * specularTermination * dirLightColor;

    // # Texture Color
    // ---------------
    vec3 color = texture(material.texture, vUV).rgb;
    vec3 textureColor = (color != vec3(0.0,0.0,0.0) ? color * material.tint : material.tint);

    // # Fragment Output
    // -----------------
    vec3 result = (ambient + diffuse + specular) * textureColor;
    fragColor = vec4(result, 1);
}
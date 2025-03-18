#version 430 core

struct Material {
    sampler2D texture;
    vec3 tint;
    sampler2D specular;
    float specularMul;
    sampler2D smoothness;
    float smoothnessMul;
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

    float smoothnessValue = texture(material.smoothness, vUV).r * material.smoothnessMul;
    float specularTermination = pow(max(0.0, dot(reflectDir, viewDir)), 64. * smoothnessValue);
    float specularIntensity = texture(material.specular, vUV).r * material.specularMul;
    vec3 specular = specularTermination * specularIntensity * dirLightColor;

    // # Texture Color
    // ---------------
    vec3 textureColor = texture(material.texture, vUV).rgb;
    vec3 color = textureColor * material.tint;

    // # Fragment Output
    // -----------------
    vec3 result = (ambient + diffuse + specular) * color;
    fragColor = vec4(result, 1);
}
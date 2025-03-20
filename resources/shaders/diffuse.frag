#version 430 core

#define MAX_LIGHTS 2

struct Material {
    sampler2D texture;
    vec3 tint;
};

struct Light {
    vec3 position;
    vec3 direction;
    vec3 color;
    float cutoff;
    float outerCutoff;
};

in vec4 vPos;
in vec4 vCol;
in vec2 vUV;
in vec3 vNorm;

out vec4 fragColor;

layout (location = 3) uniform vec3 ambientColor;
layout (location = 4) uniform vec3 dirLightColor;
layout (location = 5) uniform vec3 dirLightDirection;
uniform Light lights[MAX_LIGHTS];

uniform Material material;

void add_light(in vec3 norm, in vec3 lightDir, in vec3 lightColor, inout vec3 diffuse) {
    float diff = max(0., dot(norm, -lightDir));
    diffuse += diff * lightColor;
}

void main() 
{
    // # Ambient Lighting
    // ------------------
    vec3 ambient = ambientColor.rgb;

    // # Diffuse Lighting
    // ------------------
    vec3 diffuse = vec3(0);

    // scene sun
    add_light(normalize(vNorm), normalize(dirLightDirection), dirLightColor, diffuse);

    // scene lights
    float constant =  1.0;
    float linear = 0.22;
    float quadratic = 0.20;

    for (int i = 0; i < MAX_LIGHTS; i++) {
        vec3 lightDiffuse = vec3(0);

        vec3 norm = normalize(vNorm);
        vec3 lightDir = normalize(vPos.xyz - lights[i].position);

        // spotlight cutoff
        float theta = dot(lightDir, normalize(lights[i].direction));

        if (theta > lights[i].cutoff) {
            add_light(norm, lightDir, lights[i].color, lightDiffuse);

            // ## Attenuation
            // --------------
            float dist = length(vPos.xyz - lights[i].position);
            float attenuation = 1.0 / (constant + linear * dist + quadratic * (dist * dist));

            diffuse += lightDiffuse * attenuation;
        }
    }

    // # Texture Color
    // ---------------
    vec3 color = texture(material.texture, vUV).rgb * material.tint;

    // # Fragment Output
    // -----------------
    vec3 result = (ambient + diffuse) * color;
    fragColor = vec4(result, 1.);
}
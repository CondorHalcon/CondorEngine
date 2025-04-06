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
in vec4 vLight;

out vec4 fragColor;

layout (location = 4) uniform vec3 ambientColor;
layout (location = 5) uniform vec3 dirLightColor;
layout (location = 6) uniform vec3 dirLightDirection;
uniform Light lights[MAX_LIGHTS];
uniform sampler2D shadowMap;

uniform Material material;

float shadow_calculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5; // transform to [0,1] range

    // get rendered depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float renderDepth = texture(shadowMap, projCoords.xy).r;
    if (projCoords.x <= 0 || projCoords.y <= 0 || projCoords.x >= 1 || projCoords.y >= 1) { renderDepth = 1; }
    // get the projected depth of the fragment from light's perspective
    float projDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float bias = max(0.05 * (1.0 - dot(normal, -lightDir)), 0.005);  
    float shadow = projDepth - bias > renderDepth && projDepth <= 1  ? 1.0 : 0.0;

    return shadow;
}

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
    vec3 sunNormal = normalize(vNorm);
    vec3 sunDir = normalize(dirLightDirection);
    add_light(sunNormal, sunDir, dirLightColor, diffuse);
    float sunShadow = shadow_calculation(vLight, sunNormal, sunDir);
    diffuse = (1.0 - sunShadow) * diffuse;

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
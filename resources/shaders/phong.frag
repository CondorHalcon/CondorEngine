#version 430 core

#define MAX_LIGHTS 2

struct Material {
    sampler2D texture;
    vec3 tint;
    sampler2D specular;
    float specularMul;
    sampler2D smoothness;
    float smoothnessMul;
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

layout (location = 4) uniform vec3 ambientLight;
layout (location = 5) uniform vec3 dirLightColor;
layout (location = 6) uniform vec3 dirLightDirection;
layout (location = 7) uniform vec3 cameraPos;
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
    float shadow = projDepth - bias > renderDepth && projDepth <= 1 ? 1.0 : 0.0; 

    return shadow;
}

void add_light(in vec3 norm, in vec3 lightDir, in vec3 lightColor, inout vec3 diffuse, inout vec3 specular) 
{
    // ## Diffuse Lighting
    // -------------------
    float diff = max(0, dot(norm, -lightDir));
    diffuse += diff * lightColor;

    // ## Specular Lighting
    // --------------------
    vec3 viewDir = normalize(cameraPos - vPos.xyz);
    vec3 reflectDir = reflect(lightDir, norm);
    
    float smoothnessValue = texture(material.smoothness, vUV).r * material.smoothnessMul;
    float specularTermination = pow(max(0.0, dot(reflectDir, viewDir)), 64. * smoothnessValue);
    float specularIntensity = texture(material.specular, vUV).r * material.specularMul;
    specular += specularTermination * specularIntensity * lightColor;
}

void main() 
{
    // # Ambient Lighting
    // ------------------
    vec3 ambient = ambientLight.rgb;

    // # Diffuse and Specular Lighting
    // -------------------------------
    vec3 diffuse = vec3(0);
    vec3 specular = vec3(0);

    // scene sun
    vec3 sunNormal = normalize(vNorm);
    vec3 sunDir = normalize(dirLightDirection);
    add_light(sunNormal, sunDir, dirLightColor, diffuse, specular);
    float sunShadow = shadow_calculation(vLight, sunNormal, sunDir);
    diffuse = (1.0 - sunShadow) * diffuse;
    specular = (1.0 - sunShadow) * specular;

    // scene lights
    float constant =  1.0;
    float linear = 0.22;
    float quadratic = 0.20;

    for (int i = 0; i < MAX_LIGHTS; i++) {
        vec3 lightDiffuse = vec3(0);
        vec3 lightSpecular = vec3(0);

        vec3 norm = normalize(vNorm);
        vec3 lightDir = normalize(vPos.xyz - lights[i].position);

        // spotlight cutoff
        float theta = dot(lightDir, normalize(lights[i].direction));
        
        if (theta > lights[i].cutoff) {
            add_light(norm, lightDir, lights[i].color, lightDiffuse, lightSpecular);

            // ## Attenuation
            // --------------
            float dist = length(vPos.xyz - lights[i].position);
            float attenuation = 1.0 / (constant + linear * dist + quadratic * (dist * dist));

            diffuse += lightDiffuse * attenuation;
            specular += lightSpecular * attenuation;
        }
    }

    // # Texture Color
    // ---------------
    vec3 textureColor = texture(material.texture, vUV).rgb;
    vec3 color = textureColor * material.tint;

    // # Fragment Output
    // -----------------
    vec3 result = (ambient + diffuse + specular) * color;
    fragColor = vec4(result, 1);
}

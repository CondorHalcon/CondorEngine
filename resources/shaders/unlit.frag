#version 430 core

struct Material {
    sampler2D texture;
    vec3 tint;
};

in vec4 vPos;
in vec4 vCol;
in vec2 vUV;

out vec4 fragColor;

uniform Material material;

void main() 
{
    // # Texture Color
    // ---------------
    vec3 color = texture(material.texture, vUV).rgb;
    vec3 textureColor = (color != vec3(0.0,0.0,0.0) ? color * material.tint : material.tint);
    
    // # Fragment Output
    // -----------------
    fragColor = vec4(textureColor, 1.0);
}
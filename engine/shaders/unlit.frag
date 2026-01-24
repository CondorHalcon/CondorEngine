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
    vec3 color = texture(material.texture, vUV).rgb * material.tint;
    
    // # Fragment Output
    // -----------------
    fragColor = vec4(color, 1.0);
}
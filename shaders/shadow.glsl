uniform sampler2D shadowMap;

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

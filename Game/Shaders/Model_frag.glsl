#version 460 core

uniform sampler2D shadowMap;

uniform vec3 u_lightPos;
uniform vec3 u_viewPos;

smooth in vec3 FragPos;
smooth in vec3 Normal;
smooth in vec2 TexCoords;
smooth in vec4 FragPosLightSpace;

out vec4 FragColor;


float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5f + 0.5f;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0f : 0.0f;

    return shadow;
}  

void main()
{
    FragColor = vec4(1.0f);
}
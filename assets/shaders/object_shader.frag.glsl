#version 450

layout(location = 0) in vec3 fragNor;
layout(location = 1) in vec2 fragTex;
layout(location = 2) in vec4 lightDirection;
layout(location = 3) in vec4 lightColour;

layout(set = 1, binding = 0) uniform sampler2D textureSampler;

layout(location = 0) out vec4 outColour;

struct DirectionalLight
{
    vec3 colour;
    vec3 direction;
    float ambientIntensity;
    float diffuseIntensity;
};

vec4 calculateDirectionalLight(vec3 normal, DirectionalLight directionalLight)
{
    float diffuseFactor = max(dot(normalize(normal), normalize(directionalLight.direction)), 0.0f);
    vec4 diffuseColour = vec4(directionalLight.colour * directionalLight.diffuseIntensity * diffuseFactor, 1.0f) ;
    vec4 ambientColour = (vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity) + (1.0) * (diffuseColour);
    return ambientColour;
}

void main() {

    DirectionalLight directionalLight;
    directionalLight.colour = vec3(lightColour);
    directionalLight.direction = vec3(lightDirection);
    directionalLight.ambientIntensity = lightDirection.w;
    directionalLight.diffuseIntensity = lightColour.w;

    outColour = texture(textureSampler, fragTex) * calculateDirectionalLight(fragNor, directionalLight);
}
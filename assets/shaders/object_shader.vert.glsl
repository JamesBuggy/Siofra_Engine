#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 nor;
layout(location = 2) in vec2 tex;

layout(set = 0, binding = 0) uniform GlobalUbo {
    mat4 projection;
    mat4 view;
    vec4 lightDirection;
    vec4 lightColour;
} globalUbo;

layout(push_constant) uniform PushModel {
    mat4 model;
} pushModel;

layout(location = 0) out vec3 fragNor;
layout(location = 1) out vec2 fragTex;
layout(location = 2) out vec4 lightDirection;
layout(location = 3) out vec4 lightColour;

void main() {
    gl_Position = globalUbo.projection * globalUbo.view * pushModel.model * vec4(pos, 1.0);
    fragNor = mat3(transpose(inverse(pushModel.model))) * nor;
    fragTex = tex;
    lightDirection = globalUbo.lightDirection;
    lightColour = globalUbo.lightColour;
}
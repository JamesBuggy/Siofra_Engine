#pragma once

#include "GLM/glm.hpp"

using Vector4 = glm::vec4;
using Vector3 = glm::vec3;
using Vector2 = glm::vec2;

using Matrix2 = glm::mat2;
using Matrix2x2 = glm::mat2x2;
using Matrix2x3 = glm::mat2x3;
using Matrix2x4 = glm::mat2x4;

using Matrix3 = glm::mat3;
using Matrix3x2 = glm::mat3x2;
using Matrix3x3 = glm::mat3x3;
using Matrix3x4 = glm::mat3x4;

using Matrix4 = glm::mat4;
using Matrix4x2 = glm::mat4x2;
using Matrix4x3 = glm::mat4x3;
using Matrix4x4 = glm::mat4x4;

struct Vertex3
{
    Vector3 position;
    Vector3 normal;
    Vector3 textureCoordinate;
};

struct ViewProjection {
    Matrix4 projection;
    Matrix4 view;
};

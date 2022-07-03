#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "math/vector2.hpp"
#include "math/vector3.hpp"

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

namespace siofraEngine::math
{
    struct Vertex3
    {
        siofraEngine::math::Vector3 position;
        siofraEngine::math::Vector3 normal;
        siofraEngine::math::Vector2 textureCoordinate;
    };

    /**
    * @brief Convert degrees to radians
    *
    * @param degrees The value in degrees to convert to radians
    * @returns The input degrees expressed in radians
    */
    inline float radians(float degrees)
    {
        return degrees * 0.01745329251994329576923690768489f;
    }

    /**
    * @brief Convert radians to degrees
    *
    * @param radians The value in radians to convert to degrees
    * @returns The input radians expressed in degrees
    */
    inline float degrees(float radians)
    {
        return radians * 57.295779513082320876798154814105f;
    }
}

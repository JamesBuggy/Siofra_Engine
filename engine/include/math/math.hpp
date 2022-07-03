#pragma once

#include "math/vector2.hpp"
#include "math/vector3.hpp"
#include "math/vector4.hpp"
#include "math/matrix4x4.hpp"

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

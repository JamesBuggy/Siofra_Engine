#pragma once

#include "math/math.hpp"
#include "math/matrix4x4.hpp"

namespace siofraEngine::systems
{
    struct ModelMatrix {
        Matrix4 model;
    };

    struct ViewProjection {
        math::Matrix4x4 projection;
        math::Matrix4x4 view;
    };
}

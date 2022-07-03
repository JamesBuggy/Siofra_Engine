#pragma once

#include "math/math.hpp"

namespace siofraEngine::systems
{
    struct ViewProjection {
        math::Matrix4x4 projection;
        math::Matrix4x4 view;
    };
}

#pragma once

#include "math/math.hpp"

namespace siofraEngine::systems
{
    struct ModelMatrix {
        Matrix4 model;
    };

    struct ViewProjection {
        Matrix4 projection;
        Matrix4 view;
    };
}

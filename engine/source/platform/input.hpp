#pragma once

#include <vector>

namespace siofraEngine::platform
{
    class Input
    {
    public:
        static std::vector<bool> getKeyState();

    };
}
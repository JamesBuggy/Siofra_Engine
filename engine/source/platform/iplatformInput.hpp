#pragma once

#include <vector>

namespace siofraEngine::platform
{
    class IPlatformInput
    {
    public:
        virtual std::vector<bool> getKeyState() = 0;
        virtual ~IPlatformInput() = default;
    };
}

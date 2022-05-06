#pragma once

#include "platform/iplatformInput.hpp"

namespace siofraEngine::platform
{
    class PlatformInput : public IPlatformInput
    {
    public:
        std::vector<bool> getKeyState() override;

    };
}
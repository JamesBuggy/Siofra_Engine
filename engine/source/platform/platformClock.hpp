#pragma once

#include "platform/iplatformClock.hpp"

namespace siofraEngine::platform
{
    class PlatformClock : public IPlatformClock
    {
    public:
        float getAbsoluteTime() override;

    };
}
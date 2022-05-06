#pragma once

namespace siofraEngine::platform
{
    class IPlatformClock
    {
    public:
        virtual float getAbsoluteTime() = 0;
        virtual ~IPlatformClock() = default;
    };
}

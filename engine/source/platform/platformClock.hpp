#pragma once

#include "platform/iplatformClock.hpp"

namespace siofraEngine::platform
{
    /**
     * @brief Wraps plaftorm specific clock logic
     */
    class PlatformClock : public IPlatformClock
    {
    public:
        /**
         * @brief Get absolute time in seconds
         * 
         * @returns Absolute time in seconds
         */
        float getAbsoluteTime() override;

    };
}

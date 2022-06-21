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
        float getAbsoluteTime() const override;

        /**
         * @brief Wait a specified number of milliseconds before returning
         *
         * @param ms Time to wait in milliseconds
         */
        void sleep(std::uint32_t ms) const override;
    };
}

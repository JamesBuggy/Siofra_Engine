#pragma once

namespace siofraEngine::platform
{
    /**
     * @brief Platform clock interface
     */
    class IPlatformClock
    {
    public:
        /**
         * @brief Get absolute time in seconds
         * 
         * @returns Absolute time in seconds
         */
        virtual float getAbsoluteTime() = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IPlatformClock() = default;
    };
}

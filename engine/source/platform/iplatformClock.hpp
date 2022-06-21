#pragma once

#include <cstdint>

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
        virtual float getAbsoluteTime() const = 0;

        /**
         * @brief Wait a specified number of milliseconds before returning
         *
         * @param ms Time to wait in milliseconds
         */
        virtual void sleep(std::uint32_t ms) const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IPlatformClock() = default;
    };
}

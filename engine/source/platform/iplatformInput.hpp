#pragma once

#include <vector>

namespace siofraEngine::platform
{
    /**
     * @brief Platform input interface
     */
    class IPlatformInput
    {
    public:
        /**
         * @brief Get current keyboard state
         * 
         * @returns Current keyboard state
         */
        virtual std::vector<bool> getKeyState() = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IPlatformInput() = default;
    };
}

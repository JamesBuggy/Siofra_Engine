#pragma once

#include "platform/iplatformInput.hpp"

namespace siofraEngine::platform
{
    /**
     * @brief Wraps plaftorm specific input logic
     */
    class PlatformInput : public IPlatformInput
    {
    public:
        /**
         * @brief Get current keyboard state
         * 
         * @returns Current keyboard state
         */
        std::vector<bool> getKeyState() override;

    };
}

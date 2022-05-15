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
         * @brief Pumps event loop
         */
        void pumpEvents() override;

        /**
         * @brief Get current keyboard state
         * 
         * @returns Current keyboard state
         */
        KeyboardState getKeyboardState() override;

        /**
         * @brief Get current mouse state
         * 
         * @param x Populated with the current mouse x position
         * @param y Populated with the current mouse y position
         * 
         * @returns Current mouse button state
         */
        MouseButtonState getMouseState(std::int32_t &x, std::int32_t &y) override;

    };
}

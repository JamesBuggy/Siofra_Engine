#pragma once

#include <vector>
#include "core/input/inputStates.hpp"

namespace siofraEngine::platform
{
    /**
     * @brief Platform input interface
     */
    class IPlatformInput
    {
    public:
        /**
         * @brief Pumps event loop
         */
        virtual void pumpEvents() = 0;

        /**
         * @brief Get current keyboard state
         * 
         * @returns Current keyboard state
         */
        virtual KeyboardState getKeyboardState() = 0;

        /**
         * @brief Get current mouse state
         * 
         * @param x Populated with the current mouse x position
         * @param y Populated with the current mouse y position
         * 
         * @returns Current mouse button state
         */
        virtual MouseButtonState getMouseState(std::int32_t &x, std::int32_t &y) = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IPlatformInput() = default;
    };
}

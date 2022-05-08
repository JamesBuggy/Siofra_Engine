#pragma once

#include <vector>
#include <memory>
#include "core/keyCodes.hpp"
#include "platform/iplatformInput.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Input system. Maintains keyboard state for the current and previous updates.
     */
    class Input
    {
    public:

        /**
         * @brief Input system constructor
         * 
         * @param platformInput Access to platform specific input logic
         */
        Input(std::unique_ptr<siofraEngine::platform::IPlatformInput> platformInput);

        /**
         * @brief Updates the current and previous keyboard state
         */
        void update();

        /**
         * @brief Check if a key has been pressed
         * 
         * @param keyCode Key to check
         */
        bool keyPressed(siofraEngine::core::KeyCode keyCode) const noexcept;

        /**
         * @brief Check if a key has been released
         * 
         * @param keyCode Key to check
         */
        bool keyReleased(siofraEngine::core::KeyCode keyCode) const noexcept;

        /**
         * @brief Check if a key is being held down
         * 
         * @param keyCode Key to check
         */
        bool keyDown(siofraEngine::core::KeyCode keyCode) const noexcept;
    
    private:
        /**
         * @brief Access to platform specific input logic
         */
        std::unique_ptr<siofraEngine::platform::IPlatformInput> platformInput{ };

        /**
         * @brief Keyboard state from the previous update
         */
        std::vector<bool> previousKeyState;

        /**
         * @brief Keyboard state from the current update
         */
        std::vector<bool> currentKeyState;

    };
}

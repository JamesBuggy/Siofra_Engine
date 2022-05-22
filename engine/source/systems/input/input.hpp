#pragma once

#include <vector>
#include <memory>
#include "core/input/keyCodes.hpp"
#include "core/input/mouseCodes.hpp"
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
         * @brief Check if a key has been pressed this update
         * 
         * @param keyCode Key to check
         * @returns true if the key is pressed this update, otherwise false
         */
        bool isPressed(siofraEngine::core::KeyCode keyCode) const noexcept;

        /**
         * @brief Check if a mouse button has been pressed this update
         * 
         * @param mouseButtonCode Mouse button to check
         * @returns true if the button is pressed this update, otherwise false
         */
        bool isPressed(siofraEngine::core::MouseButtonCode mouseButtonCode) const noexcept;

        /**
         * @brief Check if a key has been released this update
         * 
         * @param keyCode Key to check
         * @returns true if the key is released this update, otherwise false
         */
        bool isReleased(siofraEngine::core::KeyCode keyCode) const noexcept;

        /**
         * @brief Check if a mouse button has been released this update
         * 
         * @param mouseButtonCode Mouse button to check
         * @returns true if the button is released this update, otherwise false
         */
        bool isReleased(siofraEngine::core::MouseButtonCode mouseButtonCode) const noexcept;

        /**
         * @brief Check if a key is being held down
         * 
         * @param keyCode Key to check
         * @returns true if the key is held down, otherwise false
         */
        bool isDown(siofraEngine::core::KeyCode keyCode) const noexcept;

        /**
         * @brief Check if a mouse button is being held down
         * 
         * @param mouseButtonCode Mouse button to check
         * @returns true if the button is held down, otherwise false
         */
        bool isDown(siofraEngine::core::MouseButtonCode mouseButtonCode) const noexcept;

        /**
         * @brief Get current mouse x position
         * 
         * @returns current mouse x position
         */
        int getMouseX() const noexcept;

        /**
         * @brief Get current mouse y position
         * 
         * @returns current mouse y position
         */
        int getMouseY() const noexcept;
    
    private:
        /**
         * @brief Access to platform specific input logic
         */
        std::unique_ptr<siofraEngine::platform::IPlatformInput> platformInput{ };

        /**
         * @brief Keyboard state from the previous update
         */
        KeyboardState previousKeyboardState;

        /**
         * @brief Keyboard state from the current update
         */
        KeyboardState currentKeyboardState;

        /**
         * @brief Mouse state from the previous update
         */
        MouseState previousMouseState;

        /**
         * @brief Mouse state from the current update
         */
        MouseState currentMouseState;

    };
}

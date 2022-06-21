#pragma once

#include "defines.hpp"
#include "core/input/keyCodes.hpp"
#include "core/input/mouseCodes.hpp"

namespace siofraEngine::core
{
    class SE_API IInputState
    {
    public:

        /**
         * @brief Check if a key has been pressed this update
         *
         * @param keyCode Key to check
         * @returns true if the key is pressed this update, otherwise false
         */
        virtual bool isPressed(siofraEngine::core::KeyCode keyCode) const noexcept = 0;

        /**
         * @brief Check if a mouse button has been pressed this update
         *
         * @param mouseButtonCode Mouse button to check
         * @returns true if the button is pressed this update, otherwise false
         */
        virtual bool isPressed(siofraEngine::core::MouseButtonCode mouseButtonCode) const noexcept = 0;

        /**
         * @brief Check if a key has been released this update
         *
         * @param keyCode Key to check
         * @returns true if the key is released this update, otherwise false
         */
        virtual bool isReleased(siofraEngine::core::KeyCode keyCode) const noexcept = 0;

        /**
         * @brief Check if a mouse button has been released this update
         *
         * @param mouseButtonCode Mouse button to check
         * @returns true if the button is released this update, otherwise false
         */
        virtual bool isReleased(siofraEngine::core::MouseButtonCode mouseButtonCode) const noexcept = 0;

        /**
         * @brief Check if a key is being held down
         *
         * @param keyCode Key to check
         * @returns true if the key is held down, otherwise false
         */
        virtual bool isDown(siofraEngine::core::KeyCode keyCode) const noexcept = 0;

        /**
         * @brief Check if a mouse button is being held down
         *
         * @param mouseButtonCode Mouse button to check
         * @returns true if the button is held down, otherwise false
         */
        virtual bool isDown(siofraEngine::core::MouseButtonCode mouseButtonCode) const noexcept = 0;

        /**
         * @brief Get current mouse x position
         *
         * @returns current mouse x position
         */
        virtual int getMouseX() const noexcept = 0;

        /**
         * @brief Get current mouse y position
         *
         * @returns current mouse y position
         */
        virtual int getMouseY() const noexcept = 0;

        /**
         * @brief Get change in mouse x position
         *
         * @returns Change in mouse x position
         */
        virtual int getMouseXChange() const noexcept = 0;

        /**
         * @brief Get change in mouse y position
         *
         * @returns Change in mouse y position
         */
        virtual int getMouseYChange() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IInputState() = default;
    };
}

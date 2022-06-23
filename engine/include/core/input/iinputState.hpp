#pragma once

#include "defines.hpp"
#include "core/input/keyCodes.hpp"
#include "core/input/mouseCodes.hpp"
#include "math/math.hpp"

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
         * @brief Get current mouse position within the window
         *
         * @returns current mouse position within the window
         */
        virtual Vector2 getMouseCoordWindow() const noexcept = 0;

        /**
         * @brief Get change in mouse position within the window
         *
         * @returns Change in mouse position within the window
         */
        virtual Vector2 getMouseCoordChangeWindow() const noexcept = 0;

        /**
         * @brief Get current mouse position in cartesian format
         *
         * @returns current mouse in cartesian format
         */
        virtual Vector2 getMouseCoordCartesian() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IInputState() = default;
    };
}

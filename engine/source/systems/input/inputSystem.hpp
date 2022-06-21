#pragma once

#include <vector>
#include <memory>
#include "core/logging.hpp"
#include "core/input/keyCodes.hpp"
#include "core/input/mouseCodes.hpp"
#include "core/input/iinputState.hpp"
#include "core/ecs/isceneController.hpp"
#include "platform/iplatformInput.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Input system. Maintains keyboard state for the current and previous updates.
     */
    class InputSystem : public core::IInputState
    {
    public:

        /**
         * @brief Input system constructor
         * 
         * @param platformInput Access to platform specific input logic
         */
        InputSystem(std::unique_ptr<siofraEngine::platform::IPlatformInput> platformInput);

        /**
         * @brief Updates the current and previous keyboard state
         * 
         * @param sceneController An ECS scene controller for the current scene
         * @param scene The current ECS scene
         * @param deltaTime Time since last update
         */
        void update(core::ISceneController * sceneController, core::Scene * scene, float deltaTime);

        /**
         * @brief Check if a key has been pressed this update
         * 
         * @param keyCode Key to check
         * @returns true if the key is pressed this update, otherwise false
         */
        bool isPressed(siofraEngine::core::KeyCode keyCode) const noexcept override;

        /**
         * @brief Check if a mouse button has been pressed this update
         * 
         * @param mouseButtonCode Mouse button to check
         * @returns true if the button is pressed this update, otherwise false
         */
        bool isPressed(siofraEngine::core::MouseButtonCode mouseButtonCode) const noexcept override;

        /**
         * @brief Check if a key has been released this update
         * 
         * @param keyCode Key to check
         * @returns true if the key is released this update, otherwise false
         */
        bool isReleased(siofraEngine::core::KeyCode keyCode) const noexcept override;

        /**
         * @brief Check if a mouse button has been released this update
         * 
         * @param mouseButtonCode Mouse button to check
         * @returns true if the button is released this update, otherwise false
         */
        bool isReleased(siofraEngine::core::MouseButtonCode mouseButtonCode) const noexcept override;

        /**
         * @brief Check if a key is being held down
         * 
         * @param keyCode Key to check
         * @returns true if the key is held down, otherwise false
         */
        bool isDown(siofraEngine::core::KeyCode keyCode) const noexcept override;

        /**
         * @brief Check if a mouse button is being held down
         * 
         * @param mouseButtonCode Mouse button to check
         * @returns true if the button is held down, otherwise false
         */
        bool isDown(siofraEngine::core::MouseButtonCode mouseButtonCode) const noexcept override;

        /**
         * @brief Get current mouse x position
         * 
         * @returns current mouse x position
         */
        int getMouseX() const noexcept override;

        /**
         * @brief Get current mouse y position
         * 
         * @returns current mouse y position
         */
        int getMouseY() const noexcept override;

        /**
         * @brief Get change in mouse x position
         *
         * @returns Change in mouse x position
         */
        int getMouseXChange() const noexcept override;

        /**
         * @brief Get change in mouse y position
         *
         * @returns Change in mouse y position
         */
        int getMouseYChange() const noexcept override;
    
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

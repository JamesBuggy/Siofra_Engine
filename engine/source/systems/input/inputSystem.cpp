#include "systems/input/inputSystem.hpp"

namespace siofraEngine::systems
{
    InputSystem::InputSystem(std::unique_ptr<siofraEngine::platform::IPlatformInput> platformInput, platform::IWindow & window) :
        platformInput{std::move(platformInput)},
        previousKeyboardState(static_cast<int>(siofraEngine::core::KeyCode::MAX_CODES), false),
        currentKeyboardState(static_cast<int>(siofraEngine::core::KeyCode::MAX_CODES), false),
        previousMouseState{},
        currentMouseState{},
        window{ window }
    {
        previousMouseState.buttonState.resize(static_cast<int>(siofraEngine::core::MouseButtonCode::MAX_CODES), false);
        currentMouseState.buttonState.resize(static_cast<int>(siofraEngine::core::MouseButtonCode::MAX_CODES), false);

        SE_LOG_INFO("Initialized input system");
    }

    void InputSystem::update(core::ISceneController * sceneController, core::Scene * scene, float deltaTime)
    {
        platformInput->pumpEvents();

        previousKeyboardState = std::move(currentKeyboardState);
        currentKeyboardState = platformInput->getKeyboardState();

        previousMouseState = currentMouseState;
        currentMouseState.buttonState = platformInput->getMouseState(currentMouseState.x, currentMouseState.y);

        if (sceneController)
        {
            sceneController->update(this, scene, deltaTime);
        }

        window.setCursorPosition(window.getWidth() / 2, window.getHeight() / 2);
    }

    bool InputSystem::isPressed(siofraEngine::core::KeyCode keyCode) const noexcept
    {
        int keyCodeIndex = static_cast<int>(keyCode);
        return !previousKeyboardState[keyCodeIndex] && currentKeyboardState[keyCodeIndex];
    }

    bool InputSystem::isPressed(siofraEngine::core::MouseButtonCode mouseButtonCode) const noexcept
    {
        int mouseButtonIndex = static_cast<int>(mouseButtonCode);
        return !previousMouseState.buttonState[mouseButtonIndex] && currentMouseState.buttonState[mouseButtonIndex];
    }

    bool InputSystem::isReleased(siofraEngine::core::KeyCode keyCode) const noexcept
    {
        int keyCodeIndex = static_cast<int>(keyCode);
        return previousKeyboardState[keyCodeIndex] && !currentKeyboardState[keyCodeIndex];
    }

    bool InputSystem::isReleased(siofraEngine::core::MouseButtonCode mouseButtonCode) const noexcept
    {
        int mouseButtonIndex = static_cast<int>(mouseButtonCode);
        return previousMouseState.buttonState[mouseButtonIndex] && !currentMouseState.buttonState[mouseButtonIndex];
    }
    
    bool InputSystem::isDown(siofraEngine::core::KeyCode keyCode) const noexcept
    {
        int keyCodeIndex = static_cast<int>(keyCode);
        return previousKeyboardState[keyCodeIndex] && currentKeyboardState[keyCodeIndex];
    }

    bool InputSystem::isDown(siofraEngine::core::MouseButtonCode mouseButtonCode) const noexcept
    {
        int mouseButtonIndex = static_cast<int>(mouseButtonCode);
        return previousMouseState.buttonState[mouseButtonIndex] && currentMouseState.buttonState[mouseButtonIndex];
    }

    math::Vector2 InputSystem::getMouseCoordWindow() const noexcept
    {
        return math::Vector2 {
            static_cast<float>(currentMouseState.x),
            static_cast<float>(currentMouseState.y)
        };
    }

    math::Vector2 InputSystem::getMouseCoordChangeWindow() const noexcept
    {
        return math::Vector2 {
            static_cast<float>(currentMouseState.x - previousMouseState.x),
            static_cast<float>(currentMouseState.y - previousMouseState.y)
        };
    }

    math::Vector2 InputSystem::getMouseCoordCartesian() const noexcept
    {
        return math::Vector2 {
            static_cast<float>(currentMouseState.x - static_cast<std::int32_t>(window.getWidth()) / 2),
            static_cast<float>((currentMouseState.y - static_cast<std::int32_t>(window.getHeight()) / 2) * -1)
        };
    }
}

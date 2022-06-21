#include "systems/input/inputSystem.hpp"

namespace siofraEngine::systems
{
    InputSystem::InputSystem(std::unique_ptr<siofraEngine::platform::IPlatformInput> platformInput) :
        platformInput{std::move(platformInput)},
        previousKeyboardState(static_cast<int>(siofraEngine::core::KeyCode::MAX_CODES), false),
        currentKeyboardState(static_cast<int>(siofraEngine::core::KeyCode::MAX_CODES), false),
        previousMouseState{},
        currentMouseState{}
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

    int InputSystem::getMouseX() const noexcept
    {
        return currentMouseState.x;
    }

    int InputSystem::getMouseY() const noexcept
    {
        return currentMouseState.y;
    }

    int InputSystem::getMouseXChange() const noexcept
    {
        return currentMouseState.x - previousMouseState.x;
    }

    int InputSystem::getMouseYChange() const noexcept
    {
        return currentMouseState.y - previousMouseState.y;
    }
}

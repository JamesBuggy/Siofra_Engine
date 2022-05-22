#include "systems/input/input.hpp"

namespace siofraEngine::systems
{
    Input::Input(std::unique_ptr<siofraEngine::platform::IPlatformInput> platformInput) :
        platformInput{std::move(platformInput)},
        previousKeyboardState(static_cast<int>(siofraEngine::core::KeyCode::MAX_CODES), false),
        currentKeyboardState(static_cast<int>(siofraEngine::core::KeyCode::MAX_CODES), false),
        previousMouseState{},
        currentMouseState{}
    {
        previousMouseState.buttonState.resize(static_cast<int>(siofraEngine::core::MouseButtonCode::MAX_CODES), false);
        currentMouseState.buttonState.resize(static_cast<int>(siofraEngine::core::MouseButtonCode::MAX_CODES), false);
    }

    void Input::update()
    {
        platformInput->pumpEvents();

        previousKeyboardState = std::move(currentKeyboardState);
        currentKeyboardState = platformInput->getKeyboardState();

        previousMouseState = currentMouseState;
        currentMouseState.buttonState = platformInput->getMouseState(currentMouseState.x, currentMouseState.y);
    }

    bool Input::isPressed(siofraEngine::core::KeyCode keyCode) const noexcept
    {
        int keyCodeIndex = static_cast<int>(keyCode);
        return !previousKeyboardState[keyCodeIndex] && currentKeyboardState[keyCodeIndex];
    }

    bool Input::isPressed(siofraEngine::core::MouseButtonCode mouseButtonCode) const noexcept
    {
        int mouseButtonIndex = static_cast<int>(mouseButtonCode);
        return !previousMouseState.buttonState[mouseButtonIndex] && currentMouseState.buttonState[mouseButtonIndex];
    }

    bool Input::isReleased(siofraEngine::core::KeyCode keyCode) const noexcept
    {
        int keyCodeIndex = static_cast<int>(keyCode);
        return previousKeyboardState[keyCodeIndex] && !currentKeyboardState[keyCodeIndex];
    }

    bool Input::isReleased(siofraEngine::core::MouseButtonCode mouseButtonCode) const noexcept
    {
        int mouseButtonIndex = static_cast<int>(mouseButtonCode);
        return previousMouseState.buttonState[mouseButtonIndex] && !currentMouseState.buttonState[mouseButtonIndex];
    }
    
    bool Input::isDown(siofraEngine::core::KeyCode keyCode) const noexcept
    {
        int keyCodeIndex = static_cast<int>(keyCode);
        return previousKeyboardState[keyCodeIndex] && currentKeyboardState[keyCodeIndex];
    }

    bool Input::isDown(siofraEngine::core::MouseButtonCode mouseButtonCode) const noexcept
    {
        int mouseButtonIndex = static_cast<int>(mouseButtonCode);
        return previousMouseState.buttonState[mouseButtonIndex] && currentMouseState.buttonState[mouseButtonIndex];
    }

    int Input::getMouseX() const noexcept
    {
        return currentMouseState.x;
    }

    int Input::getMouseY() const noexcept
    {
        return currentMouseState.y;
    }
}

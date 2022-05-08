#include "systems/input.hpp"

namespace siofraEngine::systems
{
    Input::Input(std::unique_ptr<siofraEngine::platform::IPlatformInput> platformInput) :
        platformInput{std::move(platformInput)},
        previousKeyState(static_cast<int>(siofraEngine::core::KeyCode::MAX_KEYS), false),
        currentKeyState(static_cast<int>(siofraEngine::core::KeyCode::MAX_KEYS), false)
    {

    }

    void Input::update()
    {
        previousKeyState = std::move(currentKeyState);
        currentKeyState = platformInput->getKeyState();
    }

    bool Input::keyPressed(siofraEngine::core::KeyCode keyCode) const noexcept
    {
        int keyCodeIndex = static_cast<int>(keyCode);
        return !previousKeyState[keyCodeIndex] && currentKeyState[keyCodeIndex];
    }

    bool Input::keyReleased(siofraEngine::core::KeyCode keyCode) const noexcept
    {
        int keyCodeIndex = static_cast<int>(keyCode);
        return previousKeyState[keyCodeIndex] && !currentKeyState[keyCodeIndex];
    }
    
    bool Input::keyDown(siofraEngine::core::KeyCode keyCode) const noexcept
    {
        int keyCodeIndex = static_cast<int>(keyCode);
        return previousKeyState[keyCodeIndex] && currentKeyState[keyCodeIndex];
    }
}

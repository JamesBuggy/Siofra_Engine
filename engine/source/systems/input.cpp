#include "systems/input.hpp"

namespace siofraEngine::systems
{
    Input::Input() :
        previousKeyState(static_cast<int>(siofraEngine::core::KeyCode::SE_MAX_KEYCODE), false),
        currentKeyState(static_cast<int>(siofraEngine::core::KeyCode::SE_MAX_KEYCODE), false)
    {

    }

    void Input::update()
    {
        previousKeyState = std::move(currentKeyState);
        currentKeyState = siofraEngine::platform::Input::getKeyState();
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

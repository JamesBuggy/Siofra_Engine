#pragma once

#include <vector>
#include "core/keyCodes.hpp"
#include "platform/input.hpp"

namespace siofraEngine::systems
{
    class Input
    {
    public:

        Input();

        void update();
        bool keyPressed(siofraEngine::core::KeyCode keyCode) const noexcept;
        bool keyReleased(siofraEngine::core::KeyCode keyCode) const noexcept;
        bool keyDown(siofraEngine::core::KeyCode keyCode) const noexcept;
    
    private:
        std::vector<bool> previousKeyState;
        std::vector<bool> currentKeyState;

    };
}

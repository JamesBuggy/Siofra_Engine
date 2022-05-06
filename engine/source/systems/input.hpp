#pragma once

#include <vector>
#include <memory>
#include "core/keyCodes.hpp"
#include "platform/iplatformInput.hpp"

namespace siofraEngine::systems
{
    class Input
    {
    public:

        Input(std::unique_ptr<siofraEngine::platform::IPlatformInput> platformInput);

        void update();
        bool keyPressed(siofraEngine::core::KeyCode keyCode) const noexcept;
        bool keyReleased(siofraEngine::core::KeyCode keyCode) const noexcept;
        bool keyDown(siofraEngine::core::KeyCode keyCode) const noexcept;
    
    private:
        std::unique_ptr<siofraEngine::platform::IPlatformInput> platformInput;
        std::vector<bool> previousKeyState;
        std::vector<bool> currentKeyState;

    };
}

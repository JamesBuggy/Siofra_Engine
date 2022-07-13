#ifdef SE_PLATFORM_WIN64

#include <map>
#include <SDL2/SDL.h>
#include "platform/platformInput.hpp"
#include "platform/win64/inputMapping.hpp"

namespace siofraEngine::platform
{
    void PlatformInput::pumpEvents()
    {
        SDL_PumpEvents();
    }

    KeyboardState PlatformInput::getKeyboardState()
    {
        Uint8 const * sdlKeyState = SDL_GetKeyboardState(nullptr);

        KeyboardState keyState(static_cast<int>(core::KeyCode::MAX_CODES), false);
        for (size_t i = 0; i < keyState.size(); ++i)
        {
            auto siofraKeyCode = static_cast<core::KeyCode>(i);
            auto sdlKeyCode = siofraToSdlKeyCodeMappings[siofraKeyCode];
            auto sdlScanCode = SDL_GetScancodeFromKey(sdlKeyCode);
            keyState[i] = sdlKeyState[sdlScanCode] == 1;
        }

        return keyState;
    }

    MouseButtonState PlatformInput::getMouseState(std::int32_t &x, std::int32_t &y)
    {
        Uint32 sdlButtons = SDL_GetMouseState(&x, &y);

        MouseButtonState mouseButtonState(static_cast<int>(core::MouseButtonCode::MAX_CODES), false);
        for (size_t i = 0; i < mouseButtonState.size(); ++i)
        {
            auto siofraMouseButtonCode = static_cast<core::MouseButtonCode>(i);
            auto sdlButtonMask = siofraToSdlmousButtonMappings[siofraMouseButtonCode];
            mouseButtonState[i] = (sdlButtons & sdlButtonMask) != 0;
        }

        return mouseButtonState;
    }
}

#endif

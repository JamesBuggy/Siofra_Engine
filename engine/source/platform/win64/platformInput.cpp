#ifdef SE_PLATFORM_WIN64

#include <map>
#include <SDL2/SDL.h>
#include "platform/platformInput.hpp"
#include "platform/win64/inputMapping.hpp"

namespace siofraEngine::platform
{
    std::vector<bool> PlatformInput::getKeyState()
    {
        SDL_PumpEvents();
        Uint8 const * sdlKeyState = SDL_GetKeyboardState(NULL);

        std::vector<bool> keyState(static_cast<int>(siofraEngine::core::KeyCode::MAX_KEYS));
        for (size_t i = 0; i < keyState.size(); ++i)
        {
            auto siofraKeyCode = static_cast<siofraEngine::core::KeyCode>(i);
            auto sdlKeyCode = siofraToSdlKeyCodeMappings[siofraKeyCode];
            auto sdlScanCode = SDL_GetScancodeFromKey(sdlKeyCode);
            keyState[i] = sdlKeyState[sdlScanCode] == 1;
        }

        return keyState;
    }
}

#endif

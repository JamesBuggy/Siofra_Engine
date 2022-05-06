#ifdef SE_PLATFORM_WIN64

#include <SDL2/SDL.h>
#include "platform/clock.hpp"

namespace siofraEngine::platform
{
    float Clock::getAbsoluteTime()
    {
        return (float)SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();
    }
}

#endif

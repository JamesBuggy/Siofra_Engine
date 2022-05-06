#ifdef SE_PLATFORM_WIN64

#include <SDL2/SDL.h>
#include "platform/platformClock.hpp"

namespace siofraEngine::platform
{
    float PlatformClock::getAbsoluteTime()
    {
        return (float)SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();
    }
}

#endif

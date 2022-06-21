#ifdef SE_PLATFORM_WIN64

#include <SDL2/SDL.h>
#include "platform/platformClock.hpp"

namespace siofraEngine::platform
{
    float PlatformClock::getAbsoluteTime() const
    {
        return (float)SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();
    }

    void PlatformClock::sleep(std::uint32_t ms) const
    {
        SDL_Delay(ms);
    }
}

#endif

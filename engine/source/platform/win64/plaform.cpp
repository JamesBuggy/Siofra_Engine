#ifdef SE_PLATFORM_WIN64

#include <SDL2/SDL.h>
#include "platform/platform.hpp"

namespace siofraEngine::platform
{
    void initialize()
    {
        SDL_Init(SDL_INIT_VIDEO);
    }

    void cleanUp()
    {
        SDL_Quit();
    }
}

#endif

#ifdef SE_PLATFORM_WIN64

#include <SDL2/SDL.h>
#include "platform/platform.hpp"

namespace siofraEngine::platform
{
    void initialize()
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }

    void cleanUp()
    {
        SDL_Quit();
    }
}

#endif

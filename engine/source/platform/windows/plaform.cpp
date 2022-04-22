#ifdef SE_PLATFORM_WINDOWS

#include <SDL2/SDL.h>
#include "platform/platform.hpp"

namespace engine::platform
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

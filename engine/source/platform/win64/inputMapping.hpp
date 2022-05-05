#ifdef SE_PLATFORM_WIN64

#include <map>
#include <SDL2/SDL.h>
#include "core/keyCodes.hpp"

std::map<siofraEngine::core::KeyCode, SDL_KeyCode> siofraToSdlKeyCodeMappings
{
    { siofraEngine::core::KeyCode::SE_A, SDL_KeyCode::SDLK_a },
    { siofraEngine::core::KeyCode::SE_B, SDL_KeyCode::SDLK_b },
    { siofraEngine::core::KeyCode::SE_C, SDL_KeyCode::SDLK_c },
    { siofraEngine::core::KeyCode::SE_D, SDL_KeyCode::SDLK_d },
    { siofraEngine::core::KeyCode::SE_E, SDL_KeyCode::SDLK_e },
    { siofraEngine::core::KeyCode::SE_F, SDL_KeyCode::SDLK_f },
    { siofraEngine::core::KeyCode::SE_G, SDL_KeyCode::SDLK_g },
    { siofraEngine::core::KeyCode::SE_H, SDL_KeyCode::SDLK_h },
    { siofraEngine::core::KeyCode::SE_I, SDL_KeyCode::SDLK_i },
    { siofraEngine::core::KeyCode::SE_J, SDL_KeyCode::SDLK_j },
    { siofraEngine::core::KeyCode::SE_K, SDL_KeyCode::SDLK_k },
    { siofraEngine::core::KeyCode::SE_L, SDL_KeyCode::SDLK_l },
    { siofraEngine::core::KeyCode::SE_M, SDL_KeyCode::SDLK_m },
    { siofraEngine::core::KeyCode::SE_N, SDL_KeyCode::SDLK_n },
    { siofraEngine::core::KeyCode::SE_O, SDL_KeyCode::SDLK_o },
    { siofraEngine::core::KeyCode::SE_P, SDL_KeyCode::SDLK_p },
    { siofraEngine::core::KeyCode::SE_Q, SDL_KeyCode::SDLK_q },
    { siofraEngine::core::KeyCode::SE_R, SDL_KeyCode::SDLK_r },
    { siofraEngine::core::KeyCode::SE_S, SDL_KeyCode::SDLK_s },
    { siofraEngine::core::KeyCode::SE_T, SDL_KeyCode::SDLK_t },
    { siofraEngine::core::KeyCode::SE_U, SDL_KeyCode::SDLK_u },
    { siofraEngine::core::KeyCode::SE_V, SDL_KeyCode::SDLK_v },
    { siofraEngine::core::KeyCode::SE_W, SDL_KeyCode::SDLK_w },
    { siofraEngine::core::KeyCode::SE_X, SDL_KeyCode::SDLK_x },
    { siofraEngine::core::KeyCode::SE_Y, SDL_KeyCode::SDLK_y },
    { siofraEngine::core::KeyCode::SE_Z, SDL_KeyCode::SDLK_z },

    { siofraEngine::core::KeyCode::SE_1, SDL_KeyCode::SDLK_1 },
    { siofraEngine::core::KeyCode::SE_2, SDL_KeyCode::SDLK_2 },
    { siofraEngine::core::KeyCode::SE_3, SDL_KeyCode::SDLK_3 },
    { siofraEngine::core::KeyCode::SE_4, SDL_KeyCode::SDLK_4 },
    { siofraEngine::core::KeyCode::SE_5, SDL_KeyCode::SDLK_5 },
    { siofraEngine::core::KeyCode::SE_6, SDL_KeyCode::SDLK_6 },
    { siofraEngine::core::KeyCode::SE_7, SDL_KeyCode::SDLK_7 },
    { siofraEngine::core::KeyCode::SE_8, SDL_KeyCode::SDLK_8 },
    { siofraEngine::core::KeyCode::SE_9, SDL_KeyCode::SDLK_9 },
    { siofraEngine::core::KeyCode::SE_0, SDL_KeyCode::SDLK_0 },

    { siofraEngine::core::KeyCode::SE_UP, SDL_KeyCode::SDLK_UP },
    { siofraEngine::core::KeyCode::SE_DOWN, SDL_KeyCode::SDLK_DOWN },
    { siofraEngine::core::KeyCode::SE_LEFT, SDL_KeyCode::SDLK_LEFT },
    { siofraEngine::core::KeyCode::SE_RIGHT, SDL_KeyCode::SDLK_RIGHT },

    { siofraEngine::core::KeyCode::SE_ESC, SDL_KeyCode::SDLK_ESCAPE }
};

#endif

#ifdef SE_PLATFORM_WIN64

#include <map>
#include <SDL2/SDL.h>
#include "core/keyCodes.hpp"

/**
 * @brief Siofra Engine to SDL key code mappings
 */
std::map<siofraEngine::core::KeyCode, SDL_KeyCode> siofraToSdlKeyCodeMappings
{
    { siofraEngine::core::KeyCode::KEY_A, SDL_KeyCode::SDLK_a },
    { siofraEngine::core::KeyCode::KEY_B, SDL_KeyCode::SDLK_b },
    { siofraEngine::core::KeyCode::KEY_C, SDL_KeyCode::SDLK_c },
    { siofraEngine::core::KeyCode::KEY_D, SDL_KeyCode::SDLK_d },
    { siofraEngine::core::KeyCode::KEY_E, SDL_KeyCode::SDLK_e },
    { siofraEngine::core::KeyCode::KEY_F, SDL_KeyCode::SDLK_f },
    { siofraEngine::core::KeyCode::KEY_G, SDL_KeyCode::SDLK_g },
    { siofraEngine::core::KeyCode::KEY_H, SDL_KeyCode::SDLK_h },
    { siofraEngine::core::KeyCode::KEY_I, SDL_KeyCode::SDLK_i },
    { siofraEngine::core::KeyCode::KEY_J, SDL_KeyCode::SDLK_j },
    { siofraEngine::core::KeyCode::KEY_K, SDL_KeyCode::SDLK_k },
    { siofraEngine::core::KeyCode::KEY_L, SDL_KeyCode::SDLK_l },
    { siofraEngine::core::KeyCode::KEY_M, SDL_KeyCode::SDLK_m },
    { siofraEngine::core::KeyCode::KEY_N, SDL_KeyCode::SDLK_n },
    { siofraEngine::core::KeyCode::KEY_O, SDL_KeyCode::SDLK_o },
    { siofraEngine::core::KeyCode::KEY_P, SDL_KeyCode::SDLK_p },
    { siofraEngine::core::KeyCode::KEY_Q, SDL_KeyCode::SDLK_q },
    { siofraEngine::core::KeyCode::KEY_R, SDL_KeyCode::SDLK_r },
    { siofraEngine::core::KeyCode::KEY_S, SDL_KeyCode::SDLK_s },
    { siofraEngine::core::KeyCode::KEY_T, SDL_KeyCode::SDLK_t },
    { siofraEngine::core::KeyCode::KEY_U, SDL_KeyCode::SDLK_u },
    { siofraEngine::core::KeyCode::KEY_V, SDL_KeyCode::SDLK_v },
    { siofraEngine::core::KeyCode::KEY_W, SDL_KeyCode::SDLK_w },
    { siofraEngine::core::KeyCode::KEY_X, SDL_KeyCode::SDLK_x },
    { siofraEngine::core::KeyCode::KEY_Y, SDL_KeyCode::SDLK_y },
    { siofraEngine::core::KeyCode::KEY_Z, SDL_KeyCode::SDLK_z },

    { siofraEngine::core::KeyCode::KEY_1, SDL_KeyCode::SDLK_1 },
    { siofraEngine::core::KeyCode::KEY_2, SDL_KeyCode::SDLK_2 },
    { siofraEngine::core::KeyCode::KEY_3, SDL_KeyCode::SDLK_3 },
    { siofraEngine::core::KeyCode::KEY_4, SDL_KeyCode::SDLK_4 },
    { siofraEngine::core::KeyCode::KEY_5, SDL_KeyCode::SDLK_5 },
    { siofraEngine::core::KeyCode::KEY_6, SDL_KeyCode::SDLK_6 },
    { siofraEngine::core::KeyCode::KEY_7, SDL_KeyCode::SDLK_7 },
    { siofraEngine::core::KeyCode::KEY_8, SDL_KeyCode::SDLK_8 },
    { siofraEngine::core::KeyCode::KEY_9, SDL_KeyCode::SDLK_9 },
    { siofraEngine::core::KeyCode::KEY_0, SDL_KeyCode::SDLK_0 },

    { siofraEngine::core::KeyCode::KEY_UP, SDL_KeyCode::SDLK_UP },
    { siofraEngine::core::KeyCode::KEY_DOWN, SDL_KeyCode::SDLK_DOWN },
    { siofraEngine::core::KeyCode::KEY_LEFT, SDL_KeyCode::SDLK_LEFT },
    { siofraEngine::core::KeyCode::KEY_RIGHT, SDL_KeyCode::SDLK_RIGHT },

    { siofraEngine::core::KeyCode::KEY_ESC, SDL_KeyCode::SDLK_ESCAPE }
};

#endif

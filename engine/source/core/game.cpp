#include "core/game.hpp"

namespace siofraEngine::core
{
    Game::Game(std::string title) :
        title{title}
    {
        SE_LOG_INFO("Game Created");
    }

    std::string Game::getTitle() const noexcept
    {
        return title;
    }
}
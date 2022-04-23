#include "core/game.hpp"

namespace engine::core
{
    Game::Game(std::string title) :
        title{title}
    {
        SE_LOG_INFO("Game Created");
    }

    std::string Game::getTitle()
    {
        return title;
    }
}
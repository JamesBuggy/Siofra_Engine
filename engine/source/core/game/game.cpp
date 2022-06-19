#include "core/game.hpp"
#include "core/game/gameImpl.hpp"

namespace siofraEngine::core
{
    Game::Game(std::string title) :
        implementation{ std::make_unique<Impl>(title) }
    {
        SE_LOG_INFO("Game Created");
    }

    Game::~Game() = default;

    std::string Game::getTitle() const noexcept
    {
        return implementation->getTitle();
    }

    Scene & Game::getScene() noexcept
    {
        return implementation->getScene();
    }
}
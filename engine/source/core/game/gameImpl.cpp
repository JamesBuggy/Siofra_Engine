#include "core/game/gameImpl.hpp"

namespace siofraEngine::core
{
    Game::Impl::Impl(std::string title) :
        title{ title }
    {

    }

    std::string Game::Impl::getTitle() const noexcept
    {
        return title;
    }

    Scene & Game::Impl::getScene() noexcept
    {
        return scene;
    }
}
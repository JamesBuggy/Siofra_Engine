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

    Scene * Game::Impl::getScene() noexcept
    {
        return &scene;
    }

    ISceneController * Game::Impl::getSceneController() noexcept
    {
        return sceneController.get();
    }

    void Game::Impl::setSceneController(std::unique_ptr<ISceneController> sceneController) noexcept
    {
        this->sceneController = std::move(sceneController);
        this->sceneController->init(&scene);
    }
}
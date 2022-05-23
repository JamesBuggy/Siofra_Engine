#include "core/application.hpp"
#include "core/applicationImpl.hpp"

namespace siofraEngine::core
{
    Application::Application(std::unique_ptr<siofraEngine::core::Game> game) :
        implementation{std::make_unique<Impl>(std::move(game))}
    {
        
    }

    Application::~Application() = default;

    void Application::execute()
    {
        implementation->execute();
    }
}
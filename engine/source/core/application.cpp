#include "core/application.hpp"

namespace siofraEngine::core
{
    Application::Application(std::unique_ptr<siofraEngine::core::Game> game) :
        window{siofraEngine::platform::Window(game->getTitle(), 100, 100, 800, 600)},
        game{std::move(game)}
    {
        SE_LOG_INFO("Application Init");
        siofraEngine::platform::initialize();
    }

    Application::~Application()
    {
        SE_LOG_INFO("Application Shutdown");
        siofraEngine::platform::cleanUp();
    }

    void Application::execute()
    {
        while(true)
        {
            window.pollEvents();
            if(window.shouldClose())
            {
                break;
            }
        }
    }
}
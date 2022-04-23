#include "core/application.hpp"

namespace engine::core
{
    Application::Application(std::unique_ptr<engine::core::Game> game) :
        window{engine::platform::Window(game->getTitle(), 100, 100, 800, 600)},
        game{std::move(game)}
    {
        SE_LOG_INFO("Application Init");
        engine::platform::initialize();
    }

    Application::~Application()
    {
        SE_LOG_INFO("Application Shutdown");
        engine::platform::cleanUp();
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
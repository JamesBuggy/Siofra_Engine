#include "core/application.hpp"

namespace engine::core
{
    Application::Application() :
        window{engine::platform::Window("Test", 100, 100, 800, 600)}
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
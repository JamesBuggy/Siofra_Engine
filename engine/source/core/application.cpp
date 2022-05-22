#include "core/application.hpp"

namespace siofraEngine::core
{
    Application::Application(std::unique_ptr<siofraEngine::core::Game> game) :
        ApplicationBase(),
        clock{std::make_unique<siofraEngine::platform::PlatformClock>()},
        window{siofraEngine::platform::Window(game->getTitle(), 100, 100, 800, 600, siofraEngine::platform::WindowFlags::WINDOW_VULKAN)},
        inputSystem{std::make_unique<siofraEngine::platform::PlatformInput>()},
        rendererSystem{window},
        game{std::move(game)}
    {
        
    }

    void Application::execute()
    {
        float lastTime{ };

        while(true)
        {
            clock.update();
            float currentTime = clock.getElapsedTime();
            float deltaTime = currentTime - lastTime;

            inputSystem.update();

            if(inputSystem.isReleased(siofraEngine::core::KeyCode::KEY_ESC))
            {
                break;
            }

            lastTime = currentTime;
        }
    }
}
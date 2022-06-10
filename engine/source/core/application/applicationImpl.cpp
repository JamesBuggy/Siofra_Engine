#include "core/application/applicationImpl.hpp"

namespace siofraEngine::core
{
    Application::Impl::Impl(std::unique_ptr<core::Game> game) :
        ApplicationBase(),
        eventSystem{ },
        clock{std::make_unique<platform::PlatformClock>()},
        window{platform::Window(game->getTitle(), 100, 100, 800, 600, platform::WindowFlags::WINDOW_VULKAN)},
        inputSystem{std::make_unique<platform::PlatformInput>()},
        rendererSystem{window, eventSystem},
        resourceSystem{std::make_unique<platform::PlatformFileSystem>(), eventSystem},
        game{std::move(game)}
    {
        
    }

    void Application::Impl::execute()
    {
        float lastTime{ };

        while(true)
        {
            clock.update();
            float currentTime = clock.getElapsedTime();
            float deltaTime = currentTime - lastTime;

            inputSystem.update();

            rendererSystem.draw();

            if(inputSystem.isReleased(core::KeyCode::KEY_ESC))
            {
                break;
            }

            lastTime = currentTime;
        }
    }
}
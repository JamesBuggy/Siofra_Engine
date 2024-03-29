#include "core/application/applicationImpl.hpp"

namespace siofraEngine::core
{
    Application::Impl::Impl(std::unique_ptr<core::Game> game) :
        ApplicationBase(),
        clock{std::make_unique<platform::PlatformClock>()},
        window{platform::Window(game->getTitle(), 100, 100, 1920, 1080, platform::WindowFlags::WINDOW_VULKAN)},
        inputSystem{std::make_unique<platform::PlatformInput>(), window },
        rendererSystem{window, ServiceLocator::get<systems::EventSystem>()},
        resourceSystem{std::make_unique<platform::PlatformFileSystem>(), ServiceLocator::get<systems::EventSystem>() },
        entityComponentSystem{ },
        audioSystem{ ServiceLocator::get<systems::EventSystem>() },
        game{std::move(game)}
    {
        
    }

    void Application::Impl::execute()
    {
        float targetFrameSeconds = 1.0f / 60;
        float lastFrameStartTime{ };

        game->init();

        while(true)
        {
            clock.update();
            float frameStartTime = clock.getElapsedTime();
            float deltaTime = frameStartTime - lastFrameStartTime;
            lastFrameStartTime = frameStartTime;

            auto scene = game->getScene();

            inputSystem.update(game->getSceneController(), scene, 0.001);

            resourceSystem.updateResources(scene);

            audioSystem.update(scene);

            rendererSystem.draw(scene);

            if(inputSystem.isReleased(core::KeyCode::KEY_ESC))
            {
                break;
            }

            /*float frameElapsedTime = clock.getElapsedTime() - frameStartTime;
            float remainingSeconds = targetFrameSeconds - frameElapsedTime;
            if (remainingSeconds > 0)
            {
                std::uint32_t remainingMs = remainingSeconds * 1000;
                if (remainingMs > 0)
                {
                    clock.sleep(remainingMs - 1);
                }
            }*/
        }
    }
}
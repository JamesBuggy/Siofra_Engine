#include "systems/renderer/rendererSystem.hpp"

namespace siofraEngine::systems
{
    RendererSystem::RendererSystem(siofraEngine::platform::IWindow &window, systems::IEventSystem & eventSystem) :
        rendererBackend{createRendererBackend(window)}
    {
        eventSystem.subscribe(EventTypes::CREATE_SHADER, std::bind(&RendererSystem::createShader, this, std::placeholders::_1));
        SE_LOG_INFO("Initialized renderer system");
    }

    void RendererSystem::draw()
    {
        rendererBackend->draw();
    }

    std::unique_ptr<IRendererBackend> RendererSystem::createRendererBackend(siofraEngine::platform::IWindow &window)
    {
        std::unique_ptr<IRendererBackend> rendererBackend(nullptr);
        siofraEngine::platform::WindowFlags windowFlags = window.getFlags();

        if((windowFlags & siofraEngine::platform::WindowFlags::WINDOW_VULKAN) == siofraEngine::platform::WindowFlags::WINDOW_VULKAN)
        {
            rendererBackend = std::make_unique<VulkanRenderer>(window);
        }

        SE_ASSERT_TRUE(rendererBackend != nullptr, "Unsupported renderer implementation");
        return rendererBackend;
    }

    void RendererSystem::createShader(EventPayload payload)
    {
        SE_LOG_INFO("RendererSystem::createShader");
    }
}
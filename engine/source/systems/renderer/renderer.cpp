#include "systems/renderer/renderer.hpp"

namespace siofraEngine::systems
{
    Renderer::Renderer(siofraEngine::platform::Window &window) :
        rendererBackend{createRendererBackend(window)}
    {
        SE_LOG_INFO("Initialized renderer system");
    }

    std::unique_ptr<IRendererBackend> Renderer::createRendererBackend(siofraEngine::platform::Window &window)
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
}
#include "systems/renderer/renderer.hpp"

namespace siofraEngine::systems
{
    Renderer::Renderer(siofraEngine::platform::Window &window) :
        rendererBackend{createRendererBackend(window.getFlags())}
    {
        SE_LOG_INFO("Initialized renderer system");
    }

    std::unique_ptr<IRendererImpl> Renderer::createRendererBackend(siofraEngine::platform::WindowFlags windowFlags)
    {
        std::unique_ptr<IRendererImpl> rendererBackend(nullptr);

        if((windowFlags & siofraEngine::platform::WindowFlags::WINDOW_VULKAN) == siofraEngine::platform::WindowFlags::WINDOW_VULKAN)
        {
            rendererBackend = std::make_unique<VulkanRenderer>();
        }

        SE_ASSERT_TRUE(rendererBackend != nullptr, "Unsupported renderer implementation");
        return rendererBackend;
    }
}
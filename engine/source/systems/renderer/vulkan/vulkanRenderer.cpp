#include "systems/renderer/vulkan/vulkanRenderer.hpp"

namespace siofraEngine::systems
{
    VulkanRenderer::VulkanRenderer(siofraEngine::platform::IWindow &window)
    {
        instance = std::make_unique<VulkanInstance>(VulkanInstance::Builder()
            .withApiVersion(1, 3)
            .withInstanceExtensions(window.getRequiredVulkanInstanceExtensions())
#ifdef DEBUG
            .withDebugUtilities()
#endif
            .build());

        surface = std::make_unique<VulkanSurface>(VulkanSurface::Builder()
            .withInstance(instance.get())
            .withWindow(&window)
            .build());
    }
}
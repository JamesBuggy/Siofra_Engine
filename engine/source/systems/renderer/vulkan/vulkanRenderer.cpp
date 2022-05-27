#include "systems/renderer/vulkan/vulkanRenderer.hpp"

namespace siofraEngine::systems
{
    VulkanRenderer::VulkanRenderer(siofraEngine::platform::IWindow &window)
    {
        instance = VulkanInstance::Builder()
            .withApiVersion(1, 3)
            .withInstanceExtensions(window.getRequiredVulkanInstanceExtensions())
#ifdef DEBUG
            .withDebugUtilities()
#endif
            .build();

        surface = VulkanSurface::Builder()
            .withInstance(instance.get())
            .withWindow(&window)
            .build();
    }
}
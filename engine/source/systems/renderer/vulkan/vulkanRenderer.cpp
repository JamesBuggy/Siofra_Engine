#include "systems/renderer/vulkan/vulkanRenderer.hpp"

namespace siofraEngine::systems
{
    VulkanRenderer::VulkanRenderer(siofraEngine::platform::IWindow &window)
    {
        instance = VulkanInstance::Builder()
            .withApiVersion(1, 3)
            .withInstanceExtensions(window.getRequiredVulkanInstanceExtensions())
            .build();
            
        SE_LOG_INFO("Created Vulkan renderer");
        SE_LOG_INFO(instance.getInstance());
    }
}
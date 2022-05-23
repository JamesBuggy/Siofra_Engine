#include "systems/renderer/vulkan/vulkanRenderer.hpp"

namespace siofraEngine::systems
{
    VulkanRenderer::VulkanRenderer(siofraEngine::platform::Window &window)
    {
        instance = VulkanInstance::Builder()
			.withInstanceExtensions(window.getRequiredVulkanInstanceExtensions())
			.build();
            
        SE_LOG_INFO("Created Vulkan renderer");
        SE_LOG_INFO(instance.getInstance());
    }
}
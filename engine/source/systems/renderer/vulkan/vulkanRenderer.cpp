#include "systems/renderer/vulkan/vulkanRenderer.hpp"

namespace siofraEngine::systems
{
    VulkanRenderer::VulkanRenderer(siofraEngine::platform::IWindow &window)
    {
#ifdef DEBUG
        std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
#else
        std::vector<const char*> validationLayers = {};
#endif

        instance = VulkanInstance::Builder()
            .withApiVersion(1, 3)
            .withInstanceExtensions(window.getRequiredVulkanInstanceExtensions())
            .withValidationLayers(validationLayers)
#ifdef DEBUG
            .withDebugUtilities()
#endif
            .build();

        surface = VulkanSurface::Builder()
            .withInstance(instance.get())
            .withWindow(&window)
            .build();

        VulkanQueue::Builder vulkanQueueBuilder;
        device = VulkanDevice::Builder(vulkanQueueBuilder)
            .withApiVersionSupport(1, 3)
            .withQueueFamilySupport(VulkanDeviceQueueFamilies::GRAPHICS | VulkanDeviceQueueFamilies::PRESENTATION | VulkanDeviceQueueFamilies::TRANSFER | VulkanDeviceQueueFamilies::COMPUTE)
            .withSurfacePresentationSupport(surface.get())
            .withInstance(instance.get())
            .withValidationLayers(validationLayers)
            .build();
    }
}
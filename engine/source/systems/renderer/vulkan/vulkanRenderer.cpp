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

        VulkanImage::Builder vulkanImageBuilder;
        swapchain = VulkanSwapchain::Builder(vulkanImageBuilder)
            .withDevice(device.get())
            .withExtents(window.getWidth(), window.getHeight())
            .withSurface(surface.get())
            .build();

        VulkanFramebuffer::Builder vulkanFramebufferBuilder;
        renderPass = VulkanRenderPass::Builder(vulkanFramebufferBuilder)
            .withDevice(device.get())
            .withSwapchain(swapchain.get())
            .withColourClearValue(0.0f, 0.0f, 0.0f, 1.0f)
            .withDepthClearValue(1.0f)
            .build();

        graphicsCommandPool = VulkanCommandPool::Builder()
            .withDevice(device.get())
            .withFlags(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
            .withQueueFamilyIndex(device->getGraphicsQueue()->getFamilyIndex())
            .build();

        graphicsCommandBuffers = VulkanCommandBuffer::Builder()
            .withCommandPool(graphicsCommandPool.get())
            .withDevice(device.get())
            .withLevel(VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            .build(renderPass->getFramebuffers().size());

        uint32_t maxFramesInFlight = swapchain->getMaxFramesInFlight();
        imageAvailable.resize(maxFramesInFlight);
        renderFinished.resize(maxFramesInFlight);
        drawFences.resize(maxFramesInFlight);

        VulkanSemaphore::Builder vulkanSemaphoreBuilder;
        vulkanSemaphoreBuilder.withDevice(device.get());
        VulkanFence::Builder vulkanFenceBuilder;
        vulkanFenceBuilder.withDevice(device.get());
        for (size_t i = 0; i < maxFramesInFlight; i++)
        {
            imageAvailable[i] = vulkanSemaphoreBuilder.build();
            renderFinished[i] = vulkanSemaphoreBuilder.build();
            drawFences[i] = vulkanFenceBuilder.build();
        }
    }

    VulkanRenderer::~VulkanRenderer()
    {
        vkDeviceWaitIdle(device->getLogicalDevice());
    }

    void VulkanRenderer::draw()
    {
        VkFence fenceHandle = drawFences[currentFrame]->getFence();

        vkWaitForFences(device->getLogicalDevice(), 1, &fenceHandle, VK_TRUE, std::numeric_limits<uint64_t>::max());
        vkResetFences(device->getLogicalDevice(), 1, &fenceHandle);

        uint32_t imageIndex = swapchain->acquireNextImage(imageAvailable[currentFrame].get());
 
        graphicsCommandBuffers[imageIndex]->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
        renderPass->begin(graphicsCommandBuffers[imageIndex].get(), imageIndex);

        renderPass->end(graphicsCommandBuffers[imageIndex].get());
        graphicsCommandBuffers[imageIndex].get()->end();

        device->getGraphicsQueue()->submit(imageAvailable[currentFrame].get(), renderFinished[currentFrame].get(), drawFences[currentFrame].get(), graphicsCommandBuffers[imageIndex].get());
        device->getPresentationQueue()->present(renderFinished[currentFrame].get(), swapchain.get(), imageIndex);

        currentFrame = (currentFrame + 1) % swapchain->getMaxFramesInFlight();
    }
}

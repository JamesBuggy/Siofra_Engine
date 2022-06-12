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

    RendererBackends VulkanRenderer::getRendererBackendType() const noexcept
    {
        return RendererBackends::VULKAN;
    }

    void VulkanRenderer::createShader(std::vector<char> vertexShaderCode, std::vector<char> fragmentShaderCode)
    {
        SE_LOG_INFO("VulkanRenderer::createShader");
        
        viewProjectionUniformBuffers.resize(swapchain->getSwapchainImages().size());
        objectShaderDescriptorSets.resize(swapchain->getSwapchainImages().size());

        objectShaderDescriptorPool = VulkanDescriptorPool::Builder()
            .withDevice(device.get())
            .withMaxSets(static_cast<uint32_t>(viewProjectionUniformBuffers.size()))
            .withPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, static_cast<uint32_t>(viewProjectionUniformBuffers.size()))
            .build();

        objectShaderDescriptorSetLayout = VulkanDescriptorSetLayout::Builder()
            .withDevice(device.get())
            .withLayoutBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT)
            .build();

        for (size_t i = 0; i < viewProjectionUniformBuffers.size(); i++)
        {
            viewProjectionUniformBuffers[i] = VulkanBuffer::Builder()
                .withDevice(device.get())
                .withBufferSize(sizeof(ViewProjection))
                .withBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
                .withMemoryPropertyFlags(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
                .build();

            objectShaderDescriptorSets[i] = VulkanDescriptorSet::Builder()
                .withDevice(device.get())
                .withDescriptorPool(objectShaderDescriptorPool.get())
                .withDescriptorSetLayout(objectShaderDescriptorSetLayout.get())
                .build();
        }
    }
}

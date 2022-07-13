#include "systems/renderer/vulkan/vulkanRenderer.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanQueueBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanImageBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanRenderPassBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanFramebufferBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanBufferBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanShaderModuleBuilder.hpp"
#include "utilities/constants.hpp"
#include "core/logging.hpp"

namespace siofraEngine::systems
{
    VulkanRenderer::VulkanRenderer(platform::IWindow const & window)
    {
#ifdef _DEBUG
        std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
#else
        std::vector<const char*> validationLayers = {};
#endif

        instance = VulkanInstance::Builder()
            .withApiVersion(1, 3)
            .withInstanceExtensions(window.getRequiredVulkanInstanceExtensions())
            .withValidationLayers(validationLayers)
#ifdef _DEBUG
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

        transferCommandPool = VulkanCommandPool::Builder()
            .withDevice(device.get())
            .withFlags(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
            .withQueueFamilyIndex(device->getTransferQueue()->getFamilyIndex())
            .build();

        uint32_t const maxFramesInFlight = swapchain->getMaxFramesInFlight();
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

    void VulkanRenderer::beginFrame()
    {
        VkFence const fenceHandle = drawFences[currentFrame]->getFence();

        vkWaitForFences(device->getLogicalDevice(), 1, &fenceHandle, VK_TRUE, std::numeric_limits<uint64_t>::max());
        vkResetFences(device->getLogicalDevice(), 1, &fenceHandle);

        currentImageIndex = swapchain->acquireNextImage(imageAvailable[currentFrame].get());

        graphicsCommandBuffers[currentImageIndex]->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
        renderPass->begin(graphicsCommandBuffers[currentImageIndex].get(), currentImageIndex);

        objectShaderPipeline->bind(graphicsCommandBuffers[currentImageIndex].get(), VK_PIPELINE_BIND_POINT_GRAPHICS);
    }

    void VulkanRenderer::setViewProjection(ViewProjection viewProjection)
    {
        viewProjectionUniformBuffers[currentImageIndex]->update(&viewProjection, sizeof(viewProjection));
    }

    void VulkanRenderer::draw(std::string material, std::string model, math::Matrix4x4 modelMatrix)
    {
        material = objectShaderSamplerDescriptorSets.contains(material) ? material : utilities::ResourceConstants::PlaceholderMaterialId;

        if (!models.contains(model))
        {
            model = utilities::ResourceConstants::PlaceholderModelId;
            material = utilities::ResourceConstants::PlaceholderMaterialId;
        }

        vkCmdPushConstants(graphicsCommandBuffers[currentImageIndex]->getCommandBuffer(), objectShaderPipeline->getPipelineLayout(), VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(math::Matrix4x4), &modelMatrix);

        std::vector<VkDescriptorSet> const descriptorSetGroup = {
           objectShaderDescriptorSets[currentImageIndex]->getDescriptorSet(),
           objectShaderSamplerDescriptorSets[material]->getDescriptorSet()
        };
        vkCmdBindDescriptorSets(
            graphicsCommandBuffers[currentImageIndex]->getCommandBuffer(),
            VK_PIPELINE_BIND_POINT_GRAPHICS,
            objectShaderPipeline->getPipelineLayout(),
            0,
            descriptorSetGroup.size(),
            descriptorSetGroup.data(),
            0,
            nullptr);

        VkDeviceSize const bufferOffset = 0;
        VkBuffer const vertexBuffers[] = { models[model].vertexBuffer->getBuffer() };
        vkCmdBindVertexBuffers(graphicsCommandBuffers[currentImageIndex]->getCommandBuffer(), 0, 1, vertexBuffers, &bufferOffset);
        for (size_t i = 0; i < models[model].indexBuffers.size(); i++)
        {
            vkCmdBindIndexBuffer(graphicsCommandBuffers[currentImageIndex]->getCommandBuffer(), models[model].indexBuffers[i]->getBuffer(), bufferOffset, VK_INDEX_TYPE_UINT32);
            vkCmdDrawIndexed(graphicsCommandBuffers[currentImageIndex]->getCommandBuffer(), models[model].indexBufferCounts[i], 1, 0, 0, 0);
        }
    }

    void VulkanRenderer::endFrame()
    {
        renderPass->end(graphicsCommandBuffers[currentImageIndex].get());
        graphicsCommandBuffers[currentImageIndex]->end();

        device->getGraphicsQueue()->submit(imageAvailable[currentFrame].get(), renderFinished[currentFrame].get(), drawFences[currentFrame].get(), graphicsCommandBuffers[currentImageIndex].get());
        device->getPresentationQueue()->present(renderFinished[currentFrame].get(), swapchain.get(), currentImageIndex);

        currentFrame = (currentFrame + 1) % swapchain->getMaxFramesInFlight();
    }

    RendererBackends VulkanRenderer::getRendererBackendType() const noexcept
    {
        return RendererBackends::VULKAN;
    }

    void VulkanRenderer::createShader(std::vector<char> const vertexShaderCode, std::vector<char> const fragmentShaderCode)
    {
        viewProjectionUniformBuffers.resize(swapchain->getSwapchainImages().size());
        objectShaderDescriptorSets.resize(swapchain->getSwapchainImages().size());

        objectShaderDescriptorPool = VulkanDescriptorPool::Builder()
            .withDevice(device.get())
            .withMaxSets(viewProjectionUniformBuffers.size())
            .withPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, viewProjectionUniformBuffers.size())
            .build();

        objectShaderDescriptorSetLayout = VulkanDescriptorSetLayout::Builder()
            .withDevice(device.get())
            .withLayoutBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT)
            .build();

        uint32_t const MAX_SAMPLER_DESCRIPTORS = 20;
        objectShaderSamplerDescriptorPool = VulkanDescriptorPool::Builder()
            .withDevice(device.get())
            .withMaxSets(MAX_SAMPLER_DESCRIPTORS)
            .withPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, MAX_SAMPLER_DESCRIPTORS)
            .build();

        objectShaderSamplerDescriptorSetLayout = VulkanDescriptorSetLayout::Builder()
            .withDevice(device.get())
            .withLayoutBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT)
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

            objectShaderDescriptorSets[i]->updateFromBuffer(viewProjectionUniformBuffers[i].get(), 0, sizeof(ViewProjection), 0, device.get());
        }

        std::unique_ptr<IVulkanShaderModule> vertexShaderModule = VulkanShaderModule::Builder()
            .withDevice(device.get())
            .withShaderCode(vertexShaderCode)
            .build();

        std::unique_ptr<IVulkanShaderModule> fragmenthaderModule = VulkanShaderModule::Builder()
            .withDevice(device.get())
            .withShaderCode(fragmentShaderCode)
            .build();

        objectShaderPipeline = VulkanPipeline::Builder()
            .withDevice(device.get())
            .withDescriptorSetLayouts({ objectShaderDescriptorSetLayout.get(), objectShaderSamplerDescriptorSetLayout.get() })
            .withVertexStage(std::move(vertexShaderModule))
            .withFragmentStage(std::move(fragmenthaderModule))
            .withPushConstantRange(VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(math::Matrix4x4))
            .withVertexInputAttributeDescription(0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(math::Vertex3, position))
            .withVertexInputAttributeDescription(0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(math::Vertex3, normal))
            .withVertexInputAttributeDescription(0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(math::Vertex3, textureCoordinate))
            .withVertexInputBindingDescription(0, sizeof(math::Vertex3), VK_VERTEX_INPUT_RATE_VERTEX)
            .withRenderPass(renderPass.get())
            .withViewportExtents(swapchain->getExtents())
            .build();

        objectShaderSampler = VulkanSampler::Builder()
            .withDevice(device.get())
            .build();
    }

    void VulkanRenderer::createMaterial(std::string const materialName, std::vector<char> const imageData, std::uint32_t const width, std::uint32_t const height, std::uint32_t const channels)
    {
        auto const stagingBuffer = VulkanBuffer::Builder()
            .withDevice(device.get())
            .withBufferSize(imageData.size())
            .withBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
            .withMemoryPropertyFlags(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
            .build();

        stagingBuffer->update(imageData.data(), imageData.size());

        auto image = VulkanImage::Builder()
            .withDevice(device.get())
            .withExtents(width, height)
            .withFormat(VK_FORMAT_R8G8B8A8_UNORM)
            .withTiling(VK_IMAGE_TILING_OPTIMAL)
            .withUsageFlags(VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT)
            .withMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
            .withAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT)
            .build();

        auto const commandBuffer = VulkanCommandBuffer::Builder()
            .withDevice(device.get())
            .withCommandPool(graphicsCommandPool.get())
            .withLevel(VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            .build();

        image->transitionImageLayout(commandBuffer.get(), device->getGraphicsQueue().get(), VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
        stagingBuffer->copyToImage(commandBuffer.get(), device->getGraphicsQueue().get(), image.get(), width, height);
        image->transitionImageLayout(commandBuffer.get(), device->getGraphicsQueue().get(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

        VkCommandBuffer commandBufferHandle = commandBuffer->getCommandBuffer();
        vkFreeCommandBuffers(device->getLogicalDevice(), graphicsCommandPool->getCommandPool(), 1, &commandBufferHandle);

        auto samplerDescriptorSet = VulkanDescriptorSet::Builder()
            .withDevice(device.get())
			.withDescriptorPool(objectShaderSamplerDescriptorPool.get())
			.withDescriptorSetLayout(objectShaderSamplerDescriptorSetLayout.get())
			.build();

        samplerDescriptorSet->updateFromImage(image.get(), objectShaderSampler.get(), 0, device.get());

        textureImages.push_back(std::move(image));
        objectShaderSamplerDescriptorSets[materialName] = std::move(samplerDescriptorSet);
    }

    void VulkanRenderer::createModel(std::string const modelName, std::vector<math::Vertex3> const vertexBuffer, std::vector<std::vector<std::uint32_t>> const indexBuffers)
    {
        auto const commandBuffer = VulkanCommandBuffer::Builder()
            .withDevice(device.get())
            .withCommandPool(graphicsCommandPool.get())
            .withLevel(VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            .build();
        
        std::vector<std::unique_ptr<IVulkanBuffer>> vulkanIndexBuffers{ };
        std::vector<std::uint32_t> vulkanIndexBufferCounts{ };
        for(auto const & indexBuffer : indexBuffers)
        {
            VkDeviceSize const bufferSize = static_cast<VkDeviceSize>(sizeof(uint32_t)) * indexBuffer.size();
            auto const stagingBuffer = VulkanBuffer::Builder()
                .withDevice(device.get())
                .withBufferSize(bufferSize)
                .withBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
                .withMemoryPropertyFlags(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
                .build();

            stagingBuffer->update(indexBuffer.data(), bufferSize);

            auto vulkanIndexBuffer = VulkanBuffer::Builder()
                .withDevice(device.get())
                .withBufferSize(bufferSize)
                .withBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
                .withMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
                .build();

            stagingBuffer->copyToBuffer(commandBuffer.get(), device->getGraphicsQueue().get(), vulkanIndexBuffer.get(), bufferSize);

            vulkanIndexBuffers.push_back(std::move(vulkanIndexBuffer));
            vulkanIndexBufferCounts.push_back(indexBuffer.size());
        }

        VkDeviceSize const bufferSize = static_cast<VkDeviceSize>(sizeof(math::Vertex3)) * vertexBuffer.size();
        auto const stagingBuffer = VulkanBuffer::Builder()
            .withDevice(device.get())
            .withBufferSize(bufferSize)
            .withBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
            .withMemoryPropertyFlags(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
            .build();

        stagingBuffer->update(vertexBuffer.data(), bufferSize);

        auto vulkanVertexBuffer = VulkanBuffer::Builder()
            .withDevice(device.get())
			.withBufferSize(bufferSize)
			.withBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)
			.withMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
			.build();

        stagingBuffer->copyToBuffer(commandBuffer.get(), device->getGraphicsQueue().get(), vulkanVertexBuffer.get(), bufferSize);

        Model model;
        model.vertexBuffer = std::move(vulkanVertexBuffer);
        model.indexBuffers = std::move(vulkanIndexBuffers);
        model.indexBufferCounts = std::move(vulkanIndexBufferCounts);
        models[modelName] = std::move(model);

        VkCommandBuffer const commandBufferHandle = commandBuffer->getCommandBuffer();
        vkFreeCommandBuffers(device->getLogicalDevice(), graphicsCommandPool->getCommandPool(), 1, &commandBufferHandle);
    }
}

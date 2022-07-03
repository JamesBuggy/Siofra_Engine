#pragma once

#include <map>
#include <vector>
#include <string>
#include "core/logging.hpp"
#include "platform/iwindow.hpp"
#include "systems/renderer/irendererBackend.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanInstanceBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanSurfaceBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanDeviceBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanQueueBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanImageBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanSwapchainBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanRenderPassBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanFramebufferBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanCommandPoolBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanCommandBufferBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanSemaphoreBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanFenceBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanBufferBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanDescriptorPoolBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanDescriptorSetLayoutBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanDescriptorSetBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanShaderModuleBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanPipelineBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanSamplerBuilder.hpp"
#include "systems/renderer/vulkan/resources/model.hpp"
#include "systems/renderer/common/models.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Renderer which uses the Vulkan graphics API
     */
    class VulkanRenderer : public IRendererBackend
    {
    public:
        /**
         * @brief VulkanRenderer constructor
         * 
         * @param window Window to be rendered to
         */
        VulkanRenderer(siofraEngine::platform::IWindow &window);

        /**
         * @brief VulkanRenderer destructor
         */
        ~VulkanRenderer();

        /**
         * @brief Begin rendering a frame
         */
        void beginFrame() override;

        /**
         * @brief Set view matrix for the current frame
         * 
         * @param view The view matrix to set
         */
        void setViewMatrix(Matrix4 view) override;

        /**
         * @brief Render a model with the specified material
         *
         * @param material The material to use
         * @param model The model to render
         * @param modelMatrix The models model matrix
         */
        void draw(std::string material, std::string model, Matrix4 modelMatrix) override;

        /**
         * @brief End rendering a frame
         */
        void endFrame() override;

        /**
         * @brief Get the renderer backend type
         * 
         * @returns The renderer backend type
         */
        RendererBackends getRendererBackendType() const noexcept override;

        /**
         * @brief Create a shader
         * 
         * @param vertexShaderCode Vertex shader code bytes
         * @param fragmentShaderCode Fragment shader code bytes
         */
        void createShader(std::vector<char> vertexShaderCode, std::vector<char> fragmentShaderCode) override;

        /**
         * @brief Create a shader pipeline. Triggered by a CREATE_SHADER event broadcast
         * 
         * @param materialName The material name
         * @param imageData Image bytes
         * @param width Image width
         * @param height Image height
         * @param channels Image channel count
         */
        void createMaterial(std::string materialName, std::vector<char> imageData, std::uint32_t width, std::uint32_t height, std::uint32_t channels) override;

        /**
         * @brief Create a model
         * 
         * @param modelName The model name
         * @param vertexBuffer Model vertices
         * @param indexBuffers Model vertex indices
         */
        void createModel(std::string modelName, std::vector<math::Vertex3> vertexBuffer, std::vector<std::vector<std::uint32_t>> indexBuffers) override;

    private:
        /**
         * @brief The vulkan instance
         */
        std::unique_ptr<IVulkanInstance> instance{ nullptr };

        /**
         * @brief Vulkan surface
         */
        std::unique_ptr<IVulkanSurface> surface{ nullptr };

        /**
         * @brief Vulkan device
         */
        std::unique_ptr<IVulkanDevice> device{ nullptr };

        /**
         * @brief Vulkan swapchain
         */
        std::unique_ptr<IVulkanSwapchain> swapchain{ nullptr };

        /**
         * @brief Vulkan render pass
         */
        std::unique_ptr<IVulkanRenderPass> renderPass{ nullptr };

        /**
         * @brief Vulkan graphics command pool
         */
        std::unique_ptr<IVulkanCommandPool> graphicsCommandPool{ nullptr };

        /**
         * @brief Vulkan graphics command buffers
         */
        std::vector<std::unique_ptr<IVulkanCommandBuffer>> graphicsCommandBuffers{ };

        /**
         * @brief Vulkan transfer command pool
         */
        std::unique_ptr<IVulkanCommandPool> transferCommandPool{ nullptr };

        /**
         * @brief Image available semaphores. Signaled when an image has become available after presentation
         */
        std::vector<std::unique_ptr<IVulkanSemaphore>> imageAvailable{ };

        /**
         * @brief Render finished semaphores. Signaled when an image has been rendered and is ready for presentation
         */
		std::vector<std::unique_ptr<IVulkanSemaphore>> renderFinished{ };

        /**
         * @brief Draw fences. Will block rendering of an image/frame until it is available. Prevents an image from being queued for rendering/presentation while it is already queued
         */
		std::vector<std::unique_ptr<IVulkanFence>> drawFences{ };

        /**
         * @brief The current image/frame to be rendered
         */
        uint32_t currentFrame{ 0 };

        /**
         * @brief The index of the current swapchain image being rendered to
         */
        uint32_t currentImageIndex{ 0 };

        /**
         * @brief Buffers containing view projection data for each image/frame
         */
        std::vector<std::unique_ptr<IVulkanBuffer>> viewProjectionUniformBuffers{ };

        /**
         * @brief Descriptor pool for the object shader
         */
        std::unique_ptr<IVulkanDescriptorPool> objectShaderDescriptorPool{ };

        /**
         * @brief Descriptor set layout for the object shader
         */
        std::unique_ptr<IVulkanDescriptorSetLayout> objectShaderDescriptorSetLayout{ };

        /**
         * @brief Descriptor sets for the object shader
         */
        std::vector<std::unique_ptr<IVulkanDescriptorSet>> objectShaderDescriptorSets{ };

         /**
         * @brief Object shader sampler
         */
        std::unique_ptr<IVulkanSampler> objectShaderSampler{ };

        /**
         * @brief Descriptor pool for the object shader sampler
         */
        std::unique_ptr<IVulkanDescriptorPool> objectShaderSamplerDescriptorPool{ };

        /**
         * @brief Descriptor set layout for the object shader sampler
         */
        std::unique_ptr<IVulkanDescriptorSetLayout> objectShaderSamplerDescriptorSetLayout{ };

        /**
         * @brief Descriptor sets for the object shader sampler textures
         */
        std::map<std::string, std::unique_ptr<IVulkanDescriptorSet>> objectShaderSamplerDescriptorSets{ };

        /**
         * @brief Pipeline for the object shader sampler
         */
        std::unique_ptr<IVulkanPipeline> objectShaderPipeline{ };

        /**
         * @brief Vulkan images for textures loaded by the renderer
         */
        std::vector<std::unique_ptr<IVulkanImage>> textureImages{ };

        /**
         * @brief Contains vertex and index buffers of loaded models
         */
        std::map<std::string, Model> models{ };

        /**
         * @brief Default view projection
         */
        ViewProjection defaultViewProjection{ };
    };
}

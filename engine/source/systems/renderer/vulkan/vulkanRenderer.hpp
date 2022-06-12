#pragma once

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
         * @brief Draw current frame
         */
        void draw() override;

        /**
         * @brief Get the renderer backend type
         * 
         * @returns The renderer backend type
         */
        RendererBackends getRendererBackendType() const noexcept override;

        /**
         * @brief Create a shader
         */
        void createShader(std::vector<char> vertexShaderCode, std::vector<char> fragmentShaderCode) const noexcept override;

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
    };
}

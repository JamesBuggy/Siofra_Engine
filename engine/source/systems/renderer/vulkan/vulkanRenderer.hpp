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
    };
}

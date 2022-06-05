#pragma once

#include <stdexcept>
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanRenderPassBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanFramebufferBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/vulkanRenderPass.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan render pass builder
     */
    class VulkanRenderPass::Builder : public IVulkanRenderPassBuilder
    {
    public:
        /**
         * @brief Vulkan render pass builder constructor
         * 
         * @param vulkanFramebufferBuilder Vulkan framebuffer builder
         */
        Builder(IVulkanFramebufferBuilder& vulkanFramebufferBuilder);

        /**
         * @brief Specify the vulkan device which will be used to create the render pass
         * 
         * @param device The vulkan device which will be used to create the render pass
         * @returns Reference to the Vulkan render pass builder
         */
        IVulkanRenderPassBuilder& withDevice(IVulkanDevice const * device) noexcept override;

        /**
         * @brief Specify the vulkan swapchain which will provide details to the render pass
         * 
         * @param swapchain The vulkan swapchain which will provide details to the render pass
         * @returns Reference to the Vulkan render pass builder
         */
        IVulkanRenderPassBuilder& withSwapchain(IVulkanSwapchain const * swapchain) noexcept override;

        /**
         * @brief Specify the render pass colour clear value
         * 
         * @param red The red component of the render pass colour clear value
         * @param green The green component of the render pass colour clear value
         * @param blue The blue component of the render pass colour clear value
         * @param alpha The alpha component of the render pass colour clear value
         * @returns Reference to the Vulkan render pass builder
         */
        IVulkanRenderPassBuilder& withColourClearValue(float red, float green, float blue, float alpha) noexcept override;

        /**
         * @brief Specify the render pass depth clear value
         * 
         * @param depthClearValue The render pass depth clear value
         * @returns Reference to the Vulkan render pass builder
         */
        IVulkanRenderPassBuilder& withDepthClearValue(float depthClearValue) noexcept override;

        /**
         * @brief Build the Vulkan render pass
         * 
         * @returns The final Vulkan render pass
         */
        std::unique_ptr<IVulkanRenderPass> build() const override;

    private:
        /**
         * @brief Vulkan framebuffer builder
         */
        IVulkanFramebufferBuilder& vulkanFramebufferBuilder;

        /**
         * @brief The render pass colour clear value
         */
        VkClearValue colourClearValue{ };

        /**
         * @brief The render pass depth clear value
         */
        VkClearValue depthClearValue{ };

        /**
         * @brief The vulkan device which will be used to create the render pass
         */
        IVulkanDevice const * device{ nullptr };

        /**
         * @brief The vulkan swapchain which will provide details to the render pass
         */
        IVulkanSwapchain const * swapchain{ nullptr };
    };
}

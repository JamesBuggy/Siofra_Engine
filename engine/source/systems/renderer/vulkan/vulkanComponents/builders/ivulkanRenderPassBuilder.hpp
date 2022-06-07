#pragma once

#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanRenderPass.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanSwapchain.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan render pass builder interface
     */
    class IVulkanRenderPassBuilder
    {
    public:
        /**
         * @brief Specify the vulkan device which will be used to create the render pass
         * 
         * @param device The vulkan device which will be used to create the render pass
         * @returns Reference to the Vulkan render pass builder
         */
        virtual IVulkanRenderPassBuilder& withDevice(IVulkanDevice const * device) noexcept = 0;

        /**
         * @brief Specify the vulkan swapchain which will provide details to the render pass
         * 
         * @param swapchain The vulkan swapchain which will provide details to the render pass
         * @returns Reference to the Vulkan render pass builder
         */
        virtual IVulkanRenderPassBuilder& withSwapchain(IVulkanSwapchain const * swapchain) noexcept = 0;

        /**
         * @brief Specify the render pass colour clear value
         * 
         * @param red The red component of the render pass colour clear value
         * @param green The green component of the render pass colour clear value
         * @param blue The blue component of the render pass colour clear value
         * @param alpha The alpha component of the render pass colour clear value
         * @returns Reference to the Vulkan render pass builder
         */
        virtual IVulkanRenderPassBuilder& withColourClearValue(float red, float green, float blue, float alpha) noexcept = 0;

        /**
         * @brief Specify the render pass depth clear value
         * 
         * @param depthClearValue The render pass depth clear value
         * @returns Reference to the Vulkan render pass builder
         */
        virtual IVulkanRenderPassBuilder& withDepthClearValue(float depthClearValue) noexcept = 0;

        /**
         * @brief Build the Vulkan render pass
         * 
         * @returns The final Vulkan render pass
         */
        virtual std::unique_ptr<IVulkanRenderPass> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanRenderPassBuilder() = default;
    };
}

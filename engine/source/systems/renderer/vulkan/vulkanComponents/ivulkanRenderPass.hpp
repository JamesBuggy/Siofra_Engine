#pragma once

#include <memory>
#include <vector>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanFramebuffer.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanCommandBuffer.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan render pass interface
     */
    class IVulkanRenderPass : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the vulkan render pass handle
         * 
         * @returns The vulkan render pass handle
         */
        virtual VkRenderPass getRenderPass() const noexcept = 0;

        /**
         * @brief Get the vulkan render pass framebuffers
         * 
         * @returns The vulkan render pass framebuffers
         */
        virtual std::vector<std::unique_ptr<IVulkanFramebuffer>> const & getFramebuffers() const noexcept = 0;

        /**
         * @brief Begin the render pass
         * 
         * @param commandBuffer The command buffer in which to record the command
         * @param framebufferIndex The framebuffer containing the attachments that are used with the render pass
         */
        virtual void begin(IVulkanCommandBuffer const * commandBuffer, uint32_t framebufferIndex) const = 0;

        /**
         * @brief End the render pass
         * 
         * @param commandBuffer The command command buffer in which to end the current render pass instance
         */
        virtual void end(IVulkanCommandBuffer const * commandBuffer) const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanRenderPass() = default;
    };
}

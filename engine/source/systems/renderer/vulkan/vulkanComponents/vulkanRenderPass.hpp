#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanRenderPass.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanFramebuffer.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Maintains a vulkan render pass handle
     */
    class VulkanRenderPass : public IVulkanRenderPass
    {
    public:
        /**
         * @brief VulkanRenderPass builder
         */
        class Builder;

        /**
         * @brief VulkanRenderPass constructor
         * 
         * @param renderPass Vulkan render pass handle
         * @param renderAreaOffset Vulkan render pass area offset
         * @param renderAreaExtents Vulkan render pass area extents
         * @param clearValues Vulkan render pass clear colours
         * @param framebuffers Vulkan render pass framebuffers
         * @param device Vulkan device used to create the render pass
         */
        VulkanRenderPass(VkRenderPass renderPass, VkOffset2D renderAreaOffset, VkExtent2D renderAreaExtents, std::vector<VkClearValue> clearValues, std::vector<std::unique_ptr<IVulkanFramebuffer>> framebuffers, IVulkanDevice const * device);

        /**
         * @brief VulkanRenderPass copy constructor
         * 
         * @param other VulkanRenderPass to copy
         */
        VulkanRenderPass(VulkanRenderPass const &other) = delete;

        /**
         * @brief VulkanRenderPass move constructor
         * 
         * @param other VulkanRenderPass to move
         */
        VulkanRenderPass(VulkanRenderPass &&other) noexcept;

        /**
         * @brief VulkanRenderPass destructor
         */
        ~VulkanRenderPass();

        /**
         * @brief VulkanRenderPass copy assignment
         * 
         * @param other VulkanRenderPass to copy
         */
        VulkanRenderPass& operator=(const VulkanRenderPass &other) = delete;

        /**
         * @brief VulkanRenderPass move assignment
         * 
         * @param other VulkanRenderPass to move
         */
        VulkanRenderPass& operator=(VulkanRenderPass &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;

        /**
         * @brief Get the vulkan render pass handle
         * 
         * @returns The vulkan render pass handle
         */
        VkRenderPass getRenderPass() const noexcept override;

        /**
         * @brief Get the vulkan render pass framebuffers
         * 
         * @returns The vulkan render pass framebuffers
         */
        std::vector<std::unique_ptr<IVulkanFramebuffer>> const & getFramebuffers() const noexcept override;

        /**
         * @brief Begin the render pass
         * 
         * @param commandBuffer The command buffer in which to record the command
         * @param framebufferIndex The framebuffer containing the attachments that are used with the render pass
         */
        void begin(IVulkanCommandBuffer const * commandBuffer, uint32_t framebufferIndex) const override;

        /**
         * @brief End the render pass
         * 
         * @param commandBuffer The command command buffer in which to end the current render pass instance
         */
        void end(IVulkanCommandBuffer const * commandBuffer) const override;

    private:
        /**
         * @brief Vulkan render pass handle
         */
        VkRenderPass renderPass{ VK_NULL_HANDLE };

        /**
         * @brief Vulkan render pass area offset
         */
        VkOffset2D renderAreaOffset{ 0, 0 };

        /**
         * @brief Vulkan render pass area extents
         */
        VkExtent2D renderAreaExtents{ 0, 0 };

        /**
         * @brief Vulkan render pass clear colours
         */
        std::vector<VkClearValue> clearValues{ };

        /**
         * @brief Vulkan render pass framebuffers
         */
        std::vector<std::unique_ptr<IVulkanFramebuffer>> framebuffers;

        /**
         * @brief Vulkan device used to create the render pass
         */
        IVulkanDevice const * device{ nullptr };
    };
}

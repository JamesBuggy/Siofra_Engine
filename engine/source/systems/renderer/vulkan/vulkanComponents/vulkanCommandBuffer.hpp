#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanCommandBuffer.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan command buffer
     */
    class VulkanCommandBuffer : public IVulkanCommandBuffer
    {
    public:
        /**
         * @brief VulkanCommandBuffer builder
         */
        class Builder;

        /**
         * @brief VulkanCommandBuffer constructor
         * 
         * @param commandBuffer Vulkan command buffer handle
         */
        VulkanCommandBuffer(VkCommandBuffer commandBuffer);

        /**
         * @brief VulkanCommandBuffer copy constructor
         * 
         * @param other VulkanCommandBuffer to copy
         */
        VulkanCommandBuffer(VulkanCommandBuffer const &other) = delete;

        /**
         * @brief VulkanCommandBuffer move constructor
         * 
         * @param other VulkanCommandBuffer to move
         */
        VulkanCommandBuffer(VulkanCommandBuffer &&other) noexcept;

        /**
         * @brief VulkanCommandBuffer copy assignment
         * 
         * @param other VulkanCommandBuffer to copy
         */
        VulkanCommandBuffer& operator=(const VulkanCommandBuffer &other) = delete;

        /**
         * @brief VulkanCommandBuffer move assignment
         * 
         * @param other VulkanCommandBuffer to move
         */
        VulkanCommandBuffer& operator=(VulkanCommandBuffer &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;

        /**
         * @brief Get the Vulkan command buffer handle
         * 
         * @returns The Vulkan command buffer handle
         */
        VkCommandBuffer getCommandBuffer() const noexcept override;

    private:
        /**
         * @brief Vulkan command buffer handle
         */
        VkCommandBuffer commandBuffer{ VK_NULL_HANDLE };
    };
}

#pragma once

#include <stdexcept>
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

        /**
         * @brief Start recording on the command buffer
         * 
         * @param flags Usage behavior for the command buffer
         */
        void begin(VkCommandBufferUsageFlags flags) const override;

        /**
         * @brief Stop recording on the command buffer
         */
        void end() const override;

    private:
        /**
         * @brief Vulkan command buffer handle
         */
        VkCommandBuffer commandBuffer{ VK_NULL_HANDLE };
    };
}

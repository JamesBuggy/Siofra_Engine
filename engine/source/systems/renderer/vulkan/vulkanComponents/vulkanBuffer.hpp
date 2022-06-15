#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanBuffer.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan buffer
     */
    class VulkanBuffer : public IVulkanBuffer
    {
    public:
        /**
         * @brief VulkanBuffer builder
         */
        class Builder;

        /**
         * @brief VulkanBuffer constructor
         * 
         * @param buffer Vulkan buffer handle
         * @param bufferMemory Vulkan buffer memory handle
         * @param device Vulkan device used to create the buffer
         */
        VulkanBuffer(VkBuffer buffer, VkDeviceMemory bufferMemory, IVulkanDevice const * device);

        /**
         * @brief VulkanBuffer copy constructor
         * 
         * @param other VulkanBuffer to copy
         */
        VulkanBuffer(VulkanBuffer const &other) = delete;

        /**
         * @brief VulkanBuffer move constructor
         * 
         * @param other VulkanBuffer to move
         */
        VulkanBuffer(VulkanBuffer &&other) noexcept;

        /**
         * @brief VulkanBuffer destructor
         */
        ~VulkanBuffer();

        /**
         * @brief VulkanBuffer copy assignment
         * 
         * @param other VulkanBuffer to copy
         */
        VulkanBuffer& operator=(const VulkanBuffer &other) = delete;

        /**
         * @brief VulkanBuffer move assignment
         * 
         * @param other VulkanBuffer to move
         */
        VulkanBuffer& operator=(VulkanBuffer &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;
        
        /**
         * @brief Get the Vulkan buffer handle
         * 
         * @returns The Vulkan buffer handle
         */
        VkBuffer getBuffer() const noexcept override;

        /**
         * @brief Update buffer contents
         * 
         * @param data New data to copy to the buffer
         * @param size Size of the data to copy in bytes
         */
        void update(void const * data, size_t size) const override;

        /**
         * @brief Copy the buffer to an image
         * 
         * @param commandBuffer Buffer to record commands on
         * @param queue Queue to submit recorded commands to
         * @param image The image to copy the buffer to
         * @param width The image width
         * @param height The image height
         */
        void copyToImage(IVulkanCommandBuffer const * commandBuffer, IVulkanQueue const * queue, IVulkanImage const * image, uint32_t width, uint32_t height) const override;

        /**
         * @brief Copy the buffer to another buffer
         * 
         * @param commandBuffer Buffer to record commands on
         * @param queue Queue to submit recorded commands to
         * @param destinationBuffer The destination buffer
         * @param bytes The number of bytes to copy
         */
        void copyToBuffer(IVulkanCommandBuffer const * commandBuffer, IVulkanQueue const * queue, IVulkanBuffer const * destinationBuffer, VkDeviceSize bytes) const override;

    private:
        /**
         * @brief Vulkan buffer handle
         */
        VkBuffer buffer{ VK_NULL_HANDLE };

        /**
         * @brief Vulkan buffer memory handle
         */
        VkDeviceMemory bufferMemory{ VK_NULL_HANDLE };

        /**
         * @brief Vulkan device used to create the buffer
         */
        IVulkanDevice const * device{ nullptr };
    };
}

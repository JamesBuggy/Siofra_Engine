#pragma once

#include <stdexcept>
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanBufferBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/vulkanBuffer.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan buffer builder
     */
    class VulkanBuffer::Builder : public IVulkanBufferBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the buffer
         * 
         * @param device The device with which to create the buffer
         * @returns Reference to the builder
         */
        IVulkanBufferBuilder& withDevice(IVulkanDevice const * device) noexcept override;

        /**
         * @brief Specify the buffer size
         * 
         * @param bufferSize The buffer size
         * @returns Reference to the builder
         */
        IVulkanBufferBuilder& withBufferSize(VkDeviceSize bufferSize) noexcept override;

        /**
         * @brief Specify the buffer usage flags
         * 
         * @param bufferUsageFlags The buffer usage flags
         * @returns Reference to the builder
         */
        IVulkanBufferBuilder& withBufferUsageFlags(VkBufferUsageFlags bufferUsageFlags) noexcept override;

        /**
         * @brief Specify the buffer memory property flags
         * 
         * @param memoryPropertyFlags The buffer memory property flags
         * @returns Reference to the builder
         */
        IVulkanBufferBuilder& withMemoryPropertyFlags(VkMemoryPropertyFlags memoryPropertyFlags) noexcept override;

        /**
         * @brief Build the Vulkan buffer
         * 
         * @returns The final Vulkan buffer
         */
        std::unique_ptr<IVulkanBuffer> build() const override;

    private:
        /**
         * @brief The device with which to create the buffer
         */
        IVulkanDevice const * device{ nullptr };

        /**
         * @brief The buffer size
         */
        VkDeviceSize bufferSize{ 0 };

        /**
         * @brief The buffer usage flags
         */
        VkBufferUsageFlags bufferUsageFlags{ };

        /**
         * @brief The buffer memory property flags
         */
        VkMemoryPropertyFlags memoryPropertyFlags{ };

        /**
         * @brief Find the index of the required memory type, within the physical device memory properties, which satisfies the buffer memory requirements and the desired memory types
         * 
         * @param device The device to search for the required memory type index
         * @param allowedTypes The allowed buffer memory types
         * @param properties The desired buffer memory types
         * @returns The memory type index
         */
        uint32_t findMemoryTypeIndex(IVulkanDevice const * device, uint32_t allowedTypes, VkMemoryPropertyFlags properties) const;
    };
}

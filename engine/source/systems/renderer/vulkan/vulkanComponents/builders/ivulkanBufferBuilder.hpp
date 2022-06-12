#pragma once

#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanBuffer.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan buffer builder interface
     */
    class IVulkanBufferBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the buffer
         * 
         * @param device The device with which to create the buffer
         * @returns Reference to the builder
         */
        virtual IVulkanBufferBuilder& withDevice(IVulkanDevice const * device) noexcept = 0;

        /**
         * @brief Specify the buffer size
         * 
         * @param bufferSize The buffer size
         * @returns Reference to the builder
         */
        virtual IVulkanBufferBuilder& withBufferSize(VkDeviceSize bufferSize) noexcept = 0;

        /**
         * @brief Specify the buffer usage flags
         * 
         * @param bufferUsageFlags The buffer usage flags
         * @returns Reference to the builder
         */
        virtual IVulkanBufferBuilder& withBufferUsageFlags(VkBufferUsageFlags bufferUsageFlags) noexcept = 0;

        /**
         * @brief Specify the buffer memory property flags
         * 
         * @param memoryPropertyFlags The buffer memory property flags
         * @returns Reference to the builder
         */
        virtual IVulkanBufferBuilder& withMemoryPropertyFlags(VkMemoryPropertyFlags memoryPropertyFlags) noexcept = 0;

        /**
         * @brief Build the Vulkan buffer
         * 
         * @returns The final Vulkan buffer
         */
        virtual std::unique_ptr<IVulkanBuffer> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanBufferBuilder() = default;
    };
}

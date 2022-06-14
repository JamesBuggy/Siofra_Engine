#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanQueue.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanCommandBuffer.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanImage.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan buffer interface
     */
    class IVulkanBuffer : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the Vulkan buffer handle
         * 
         * @returns The Vulkan buffer handle
         */
        virtual VkBuffer getBuffer() const noexcept = 0;

        /**
         * @brief Update buffer contents
         * 
         * @param data New data to copy to the buffer
         * @param size Size of the data to copy in bytes
         */
        virtual void update(void const * data, size_t size) const = 0;

        /**
         * @brief Copy the buffer to an image
         * 
         * @param transferCommandBuffer Buffer to record commands on
         * @param transferQueue Queue to submit recorded commands to
         * @param image The image to copy the buffer to
         * @param width The image width
         * @param height The image height
         */
        virtual void copyToImage(IVulkanCommandBuffer const * transferCommandBuffer, IVulkanQueue const * transferQueue, IVulkanImage const * image, uint32_t width, uint32_t height) const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanBuffer() = default;
    };
}

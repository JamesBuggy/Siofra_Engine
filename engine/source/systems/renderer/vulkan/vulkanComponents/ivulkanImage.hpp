#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanCommandBuffer.hpp"

namespace siofraEngine::systems
{
    class IVulkanQueue;

    /**
     * @brief Vulkan image interface
     */
    class IVulkanImage : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the image view handle
         * 
         * @returns The image view handle
         */
        virtual VkImageView getImageView() const noexcept = 0;

        /**
         * @brief Get the image handle
         * 
         * @returns The image handle
         */
        virtual VkImage getImage() const noexcept = 0;

        /**
         * @brief Transition the image layout
         * 
         * @param commandBuffer The command buffer to record on
         * @param queue The queue on which to submit the command buffer
         * @param oldLayout The old image layout
         * @param newLayout The new image layout
         */
        virtual void transitionImageLayout(IVulkanCommandBuffer const * commandBuffer, IVulkanQueue const * queue, VkImageLayout oldLayout, VkImageLayout newLayout) const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanImage() = default;
    };
}

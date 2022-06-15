#pragma once

#include <memory>
#include <vector>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanCommandBuffer.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanCommandPool.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan command buffer builder interface
     */
    class IVulkanCommandBufferBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the command buffer(s)
         * 
         * @param device The device with which to create the command buffer(s)
         * @returns Reference to the builder
         */
        virtual IVulkanCommandBufferBuilder& withDevice(IVulkanDevice const * device) noexcept = 0;

        /**
         * @brief Specify the command buffer level
         * 
         * @param level The command buffer level
         * @returns Reference to the builder
         */
        virtual IVulkanCommandBufferBuilder& withLevel(VkCommandBufferLevel level) noexcept = 0;

        /**
         * @brief Specify the command pool used to allocate the command buffer(s)
         * 
         * @param commandPool The command pool used to allocate the command buffer(s)
         * @returns Reference to the builder
         */
        virtual IVulkanCommandBufferBuilder& withCommandPool(IVulkanCommandPool const * commandPool) noexcept = 0;

        /**
         * @brief Build the Vulkan command buffer(s)
         * 
         * @param count Number of command buffers to allocate
         * @returns The final Vulkan command buffer(s)
         */
        virtual std::vector<std::unique_ptr<IVulkanCommandBuffer>> build(uint32_t count) const = 0;

        /**
         * @brief Build the Vulkan command buffer
         * 
         * @returns The final Vulkan command buffer
         */
        virtual std::unique_ptr<IVulkanCommandBuffer> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanCommandBufferBuilder() = default;
    };
}

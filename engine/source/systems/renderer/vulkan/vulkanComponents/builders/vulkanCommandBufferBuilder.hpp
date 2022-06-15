#pragma once

#include <stdexcept>
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanCommandBufferBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/vulkanCommandBuffer.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan command buffer builder
     */
    class VulkanCommandBuffer::Builder : public IVulkanCommandBufferBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the command buffer(s)
         * 
         * @param device The device with which to create the command buffer(s)
         * @returns Reference to the builder
         */
        IVulkanCommandBufferBuilder& withDevice(IVulkanDevice const * device) noexcept override;

        /**
         * @brief Specify the command buffer level
         * 
         * @param level The command buffer level
         * @returns Reference to the builder
         */
        IVulkanCommandBufferBuilder& withLevel(VkCommandBufferLevel level) noexcept override;

        /**
         * @brief Specify the command pool used to allocate the command buffer(s)
         * 
         * @param commandPool The command pool used to allocate the command buffer(s)
         * @returns Reference to the builder
         */
        IVulkanCommandBufferBuilder& withCommandPool(IVulkanCommandPool const * commandPool) noexcept override;

        /**
         * @brief Build the Vulkan command buffer(s)
         * 
         * @param count Number of command buffers to allocate
         * @returns The final Vulkan command buffer(s)
         */
        std::vector<std::unique_ptr<IVulkanCommandBuffer>> build(uint32_t count) const override;

        /**
         * @brief Build the Vulkan command buffer
         * 
         * @returns The final Vulkan command buffer
         */
        std::unique_ptr<IVulkanCommandBuffer> build() const override;

    private:
        /**
         * @brief The device with which to create the command buffer
         */
        IVulkanDevice const * device{ nullptr };

        /**
         * @brief The command pool used to allocate the command buffer
         */
        IVulkanCommandPool const * commandPool{ nullptr };

        /**
         * @brief The command buffer level
         */
        VkCommandBufferLevel level{ VK_COMMAND_BUFFER_LEVEL_PRIMARY };
    };
}

#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan command buffer interface
     */
    class IVulkanCommandBuffer : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the Vulkan command buffer handle
         * 
         * @returns The Vulkan command buffer handle
         */
        virtual VkCommandBuffer getCommandBuffer() const noexcept = 0;

        /**
         * @brief Start recording on the command buffer
         * 
         * @param flags Usage behavior for the command buffer
         */
        virtual void begin(VkCommandBufferUsageFlags flags) const = 0;

        /**
         * @brief Stop recording on the command buffer
         */
        virtual void end() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanCommandBuffer() = default;
    };
}

#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

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
         * @brief Interface destructor
         */
        virtual ~IVulkanBuffer() = default;
    };
}

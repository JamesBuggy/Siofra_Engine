#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan fence interface
     */
    class IVulkanFence : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the vulkan fence handle
         * 
         * @returns The vulkan fence handle
         */
        virtual VkFence getFence() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanFence() = default;
    };
}

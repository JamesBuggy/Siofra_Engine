#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan command pool interface
     */
    class IVulkanCommandPool : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the Vulkan command pool handle
         * 
         * @returns The Vulkan command pool handle
         */
        virtual VkCommandPool getCommandPool() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanCommandPool() = default;
    };
}

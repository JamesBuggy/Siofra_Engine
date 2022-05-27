#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan instance interface
     */
    class IVulkanInstance : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the vulkan instance handle
         * 
         * @returns The vulkan instance handle
         */
        virtual VkInstance getInstance() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanInstance() = default;
    };
}

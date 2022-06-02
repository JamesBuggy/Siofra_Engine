#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan queue interface
     */
    class IVulkanQueue : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the vulkan queue handle
         * 
         * @returns The vulkan queue handle
         */
        virtual VkQueue getQueue() const noexcept = 0;

        /**
         * @brief Get the vulkan queue family index
         * 
         * @returns The vulkan queue family index
         */
        virtual uint32_t getFamilyIndex() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanQueue() = default;
    };
}

#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan surface interface
     */
    class IVulkanSurface : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the vulkan surface handle
         * 
         * @returns The vulkan surface handle
         */
        virtual VkSurfaceKHR getSurface() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanSurface() = default;
    };
}

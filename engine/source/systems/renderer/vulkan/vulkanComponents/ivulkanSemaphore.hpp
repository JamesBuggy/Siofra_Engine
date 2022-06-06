#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan semaphore interface
     */
    class IVulkanSemaphore : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the vulkan semaphore handle
         * 
         * @returns The vulkan semaphore handle
         */
        virtual VkSemaphore getSemaphore() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanSemaphore() = default;
    };
}

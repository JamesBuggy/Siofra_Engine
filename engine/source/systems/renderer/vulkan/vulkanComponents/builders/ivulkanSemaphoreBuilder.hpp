#pragma once

#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanSemaphore.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan semaphore builder interface
     */
    class IVulkanSemaphoreBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the semaphore
         * 
         * @param device The device with which to create the semaphore
         * @returns Reference to the builder
         */
        virtual IVulkanSemaphoreBuilder& withDevice(IVulkanDevice const * device) noexcept = 0;

        /**
         * @brief Build the Vulkan semaphore
         * 
         * @returns The final Vulkan semaphore
         */
        virtual std::unique_ptr<IVulkanSemaphore> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanSemaphoreBuilder() = default;
    };
}

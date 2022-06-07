#pragma once

#include <stdexcept>
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanSemaphoreBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/vulkanSemaphore.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan semaphore builder
     */
    class VulkanSemaphore::Builder : public IVulkanSemaphoreBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the semaphore
         * 
         * @param device The device with which to create the semaphore
         * @returns Reference to the builder
         */
        IVulkanSemaphoreBuilder& withDevice(IVulkanDevice const * device) noexcept override;

        /**
         * @brief Build the Vulkan semaphore
         * 
         * @returns The final Vulkan semaphore
         */
        std::unique_ptr<IVulkanSemaphore> build() const override;

    private:
        /**
         * @brief The device with which to create the semaphore
         */
        IVulkanDevice const * device{ nullptr };
    };
}

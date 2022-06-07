#pragma once

#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanFence.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan fence builder interface
     */
    class IVulkanFenceBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the fence
         * 
         * @param device The device with which to create the fence
         * @returns Reference to the builder
         */
        virtual IVulkanFenceBuilder& withDevice(IVulkanDevice const * device) noexcept = 0;

        /**
         * @brief Build the Vulkan fence
         * 
         * @returns The final Vulkan fence
         */
        virtual std::unique_ptr<IVulkanFence> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanFenceBuilder() = default;
    };
}

#pragma once

#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanSampler.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan sampler builder interface
     */
    class IVulkanSamplerBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the sampler
         * 
         * @param device The device with which to create the sampler
         * @returns Reference to the builder
         */
        virtual IVulkanSamplerBuilder& withDevice(IVulkanDevice const * device) noexcept = 0;

        /**
         * @brief Build the Vulkan sampler
         * 
         * @returns The final Vulkan sampler
         */
        virtual std::unique_ptr<IVulkanSampler> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanSamplerBuilder() = default;
    };
}

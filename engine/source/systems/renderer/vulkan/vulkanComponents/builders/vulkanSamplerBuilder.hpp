#pragma once

#include <stdexcept>
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanSamplerBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/vulkanSampler.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan sampler builder
     */
    class VulkanSampler::Builder : public IVulkanSamplerBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the sampler
         * 
         * @param device The device with which to create the sampler
         * @returns Reference to the builder
         */
        IVulkanSamplerBuilder& withDevice(IVulkanDevice const * device) noexcept override;

        /**
         * @brief Build the Vulkan sampler
         * 
         * @returns The final Vulkan sampler
         */
        std::unique_ptr<IVulkanSampler> build() const override;

    private:
        /**
         * @brief The device with which to create the sampler
         */
        IVulkanDevice const * device{ nullptr };
    };
}

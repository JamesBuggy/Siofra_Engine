#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan sampler interface
     */
    class IVulkanSampler : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the vulkan sampler handle
         * 
         * @returns The vulkan sampler handle
         */
        virtual VkSampler getSampler() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanSampler() = default;
    };
}

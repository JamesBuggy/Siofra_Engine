#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan shader module interface
     */
    class IVulkanShaderModule : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the vulkan shader module handle
         * 
         * @returns The vulkan shader module handle
         */
        virtual VkShaderModule getShaderModule() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanShaderModule() = default;
    };
}

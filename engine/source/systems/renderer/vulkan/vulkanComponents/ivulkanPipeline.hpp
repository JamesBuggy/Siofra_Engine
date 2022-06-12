#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan pipeline interface
     */
    class IVulkanPipeline : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the vulkan pipeline handle
         * 
         * @returns The vulkan pipeline handle
         */
        virtual VkPipeline getPipeline() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanPipeline() = default;
    };
}

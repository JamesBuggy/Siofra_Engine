#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan render pass interface
     */
    class IVulkanRenderPass : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the vulkan render pass handle
         * 
         * @returns The vulkan render pass handle
         */
        virtual VkRenderPass getRenderPass() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanRenderPass() = default;
    };
}

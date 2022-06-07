#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan framebuffer interface
     */
    class IVulkanFramebuffer : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the Vulkan framebuffer handle
         * 
         * @returns The Vulkan framebuffer handle
         */
        virtual VkFramebuffer getFramebuffer() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanFramebuffer() = default;
    };
}

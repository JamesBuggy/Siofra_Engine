#pragma once

#include <memory>
#include <vector>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanFramebuffer.hpp"

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
         * @brief Get the vulkan render pass framebuffers
         * 
         * @returns The vulkan render pass framebuffers
         */
        virtual std::vector<std::unique_ptr<IVulkanFramebuffer>> const & getFramebuffers() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanRenderPass() = default;
    };
}

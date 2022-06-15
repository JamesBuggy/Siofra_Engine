#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanCommandBuffer.hpp"

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
         * @brief Get the vulkan pipeline layout handle
         * 
         * @returns The vulkan pipeline layout handle
         */
        virtual VkPipelineLayout getPipelineLayout() const noexcept = 0;

        /**
         * @brief Bind the pipeline to a command buffer
         * 
         * @param commandBuffer The command buffer to bind to
         * @param pipelineBindPoint Specifies to which bind point the pipeline is bound
         */
        virtual void bind(IVulkanCommandBuffer const * commandBuffer, VkPipelineBindPoint pipelineBindPoint) const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanPipeline() = default;
    };
}

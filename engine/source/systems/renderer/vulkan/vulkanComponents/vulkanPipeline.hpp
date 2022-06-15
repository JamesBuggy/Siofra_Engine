#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanPipeline.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan pipeline
     */
    class VulkanPipeline : public IVulkanPipeline
    {
    public:
        /**
         * @brief VulkanPipeline builder
         */
        class Builder;

        /**
         * @brief VulkanPipeline constructor
         * 
         * @param pipeline Vulkan pipeline handle
         * @param pipelineLayout Vulkan pipeline layout handle
         * @param device The Vulkan device used to create the pipeline
         */
        VulkanPipeline(VkPipeline pipeline, VkPipelineLayout pipelineLayout, IVulkanDevice const * device);

        /**
         * @brief VulkanPipeline copy constructor
         * 
         * @param other VulkanPipeline to copy
         */
        VulkanPipeline(VulkanPipeline const &other) = delete;

        /**
         * @brief VulkanPipeline move constructor
         * 
         * @param other VulkanPipeline to move
         */
        VulkanPipeline(VulkanPipeline &&other) noexcept;

        /**
         * @brief VulkanPipeline destructor
         */
        ~VulkanPipeline();

        /**
         * @brief VulkanPipeline copy assignment
         * 
         * @param other VulkanPipeline to copy
         */
        VulkanPipeline& operator=(const VulkanPipeline &other) = delete;

        /**
         * @brief VulkanPipeline move assignment
         * 
         * @param other VulkanPipeline to move
         */
        VulkanPipeline& operator=(VulkanPipeline &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;
        
        /**
         * @brief Get the Vulkan pipeline handle
         * 
         * @returns The Vulkan pipeline handle
         */
        VkPipeline getPipeline() const noexcept override;

        /**
         * @brief Get the vulkan pipeline layout handle
         * 
         * @returns The vulkan pipeline layout handle
         */
        VkPipelineLayout getPipelineLayout() const noexcept override;

        /**
         * @brief Bind the pipeline to a command buffer
         * 
         * @param commandBuffer The command buffer to bind to
         * @param pipelineBindPoint Specifies to which bind point the pipeline is bound
         */
        void bind(IVulkanCommandBuffer const * commandBuffer, VkPipelineBindPoint pipelineBindPoint) const override;

    private:
        /**
         * @brief Vulkan pipeline handle
         */
        VkPipeline pipeline{ VK_NULL_HANDLE };

        /**
         * @brief Vulkan pipeline layout handle
         */
        VkPipelineLayout pipelineLayout{ VK_NULL_HANDLE };

        /**
         * @brief The Vulkan device used to create the pipeline
         */
        IVulkanDevice const * device{ nullptr };
    };
}

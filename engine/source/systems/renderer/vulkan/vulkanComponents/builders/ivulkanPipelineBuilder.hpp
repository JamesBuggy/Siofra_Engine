#pragma once

#include <memory>
#include <vector>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanPipeline.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanShaderModule.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDescriptorSetLayout.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanRenderPass.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan pipeline builder interface
     */
    class IVulkanPipelineBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the buffer
         * 
         * @param device The device with which to create the buffer
         * @returns Reference to the builder
         */
        virtual IVulkanPipelineBuilder& withDevice(IVulkanDevice const * device) noexcept = 0;

        /**
         * @brief Specify the pipeline viewport extents
         * 
         * @param viewportExtents The pipeline viewport extents
         * @returns Reference to the builder
         */
        virtual IVulkanPipelineBuilder& withViewportExtents(VkExtent2D viewportExtents) noexcept = 0;

        /**
         * @brief Specify the render pass with which the pipeline will be compatible
         * 
         * @param renderPass The render pass with which the pipeline will be compatible
         * @returns Reference to the builder
         */
        virtual IVulkanPipelineBuilder& withRenderPass(IVulkanRenderPass const * renderPass) noexcept = 0;

        /**
         * @brief Specify the descriptor set layouts to include in the pipeline layout
         * 
         * @param descriptorSetLayouts The descriptor set layouts to include in the pipeline layout
         * @returns Reference to the builder
         */
        virtual IVulkanPipelineBuilder& withDescriptorSetLayouts(std::vector<IVulkanDescriptorSetLayout const *> descriptorSetLayouts) noexcept = 0;
        
        /**
         * @brief Specify a vertex input binding description
         * 
         * @ref https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkVertexInputBindingDescription.html
         * 
         * @param binding The binding number that this structure describes
         * @param stride The byte stride between consecutive elements within the buffer
         * @param inputRate Specifies whether vertex attribute addressing is a function of the vertex index or of the instance index
         */
        virtual IVulkanPipelineBuilder& withVertexInputBindingDescription(uint32_t binding, uint32_t stride, VkVertexInputRate inputRate) noexcept = 0;

        /**
         * @brief Specify a vertex input attribute description
         * 
         * @ref https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkVertexInputAttributeDescription.html
         * 
         * @param binding The binding number which this attribute takes its data from
         * @param location The shader input location number for this attribute
         * @param format The size and type of the vertex attribute data
         * @param offset The byte offset of this attribute relative to the start of an element in the vertex input binding
         */
        virtual IVulkanPipelineBuilder& withVertexInputAttributeDescription(uint32_t binding, uint32_t location, VkFormat format, uint32_t offset) noexcept = 0;

        /**
         * @brief Specify a push constant range
         * 
         * @ref https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPushConstantRange.html
         * 
         * @param stageFlags The set of stage flags describing the shader stages that will access a range of push constants
         * @param offset The start offset. Must be multiple of 4
         * @param size The push constane size. Must be multiple of 4
         */
        virtual IVulkanPipelineBuilder& withPushConstantRange(VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size) noexcept = 0;

        /**
         * @brief Specify a pipeline shader module for the vertex stage
         * 
         * @param shaderModule The pipeline shader module
         */
        virtual IVulkanPipelineBuilder& withVertexStage(std::unique_ptr<IVulkanShaderModule> shaderModule) noexcept = 0;

        /**
         * @brief Specify a pipeline shader module for the fragment stage
         * 
         * @param shaderModule The pipeline shader module
         */
        virtual IVulkanPipelineBuilder& withFragmentStage(std::unique_ptr<IVulkanShaderModule> shaderModule) noexcept = 0;

        /**
         * @brief Build the Vulkan pipeline
         * 
         * @returns The final Vulkan pipeline
         */
        virtual std::unique_ptr<IVulkanPipeline> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanPipelineBuilder() = default;
    };
}

#pragma once

#include <stdexcept>
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanPipelineBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/vulkanPipeline.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan pipeline builder
     */
    class VulkanPipeline::Builder : public IVulkanPipelineBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the buffer
         * 
         * @param device The device with which to create the buffer
         * @returns Reference to the builder
         */
        IVulkanPipelineBuilder& withDevice(IVulkanDevice const * device) noexcept override;

        /**
         * @brief Specify the pipeline viewport extents
         * 
         * @param viewportExtents The pipeline viewport extents
         * @returns Reference to the builder
         */
        IVulkanPipelineBuilder& withViewportExtents(VkExtent2D viewportExtents) noexcept override;

        /**
         * @brief Specify the render pass with which the pipeline will be compatible
         * 
         * @param renderPass The render pass with which the pipeline will be compatible
         * @returns Reference to the builder
         */
        IVulkanPipelineBuilder& withRenderPass(IVulkanRenderPass const * renderPass) noexcept override;

        /**
         * @brief Specify the descriptor set layouts to include in the pipeline layout
         * 
         * @param descriptorSetLayouts The descriptor set layouts to include in the pipeline layout
         * @returns Reference to the builder
         */
        IVulkanPipelineBuilder& withDescriptorSetLayouts(std::vector<IVulkanDescriptorSetLayout const *> descriptorSetLayouts) noexcept override;
        
        /**
         * @brief Specify a vertex input binding description
         * 
         * @ref https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkVertexInputBindingDescription.html
         * 
         * @param binding The binding number that this structure describes
         * @param stride The byte stride between consecutive elements within the buffer
         * @param inputRate Specifies whether vertex attribute addressing is a function of the vertex index or of the instance index
         */
        IVulkanPipelineBuilder& withVertexInputBindingDescription(uint32_t binding, uint32_t stride, VkVertexInputRate inputRate) noexcept override;

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
        IVulkanPipelineBuilder& withVertexInputAttributeDescription(uint32_t binding, uint32_t location, VkFormat format, uint32_t offset) noexcept override;

        /**
         * @brief Specify a push constant range to include in the pipeline layout
         * 
         * @ref https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPushConstantRange.html
         * 
         * @param stageFlags The set of stage flags describing the shader stages that will access a range of push constants
         * @param offset The start offset. Must be multiple of 4
         * @param size The push constane size. Must be multiple of 4
         */
        IVulkanPipelineBuilder& withPushConstantRange(VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size) noexcept override;

        /**
         * @brief Specify a pipeline shader module for the vertex stage
         * 
         * @param shaderModule The pipeline shader module
         */
        IVulkanPipelineBuilder& withVertexStage(std::unique_ptr<IVulkanShaderModule> shaderModule) noexcept override;

        /**
         * @brief Specify a pipeline shader module for the fragment stage
         * 
         * @param shaderModule The pipeline shader module
         */
        IVulkanPipelineBuilder& withFragmentStage(std::unique_ptr<IVulkanShaderModule> shaderModule) noexcept override;

        /**
         * @brief Build the Vulkan pipeline
         * 
         * @returns The final Vulkan pipeline
         */
        std::unique_ptr<IVulkanPipeline> build() const override;

    private:
        /**
         * @brief The vulkan device which will be used to create the render pass
         */
        IVulkanDevice const * device{ nullptr };

        /**
         * @brief The render pass with which the pipeline will be compatible
         */
        IVulkanRenderPass const * renderPass{ nullptr };

        /**
         * @brief The pipeline viewport extents
         */
        VkExtent2D viewportExtents{ 0, 0 };

        /**
         * @brief The vertex input binding descriptions
         */
        std::vector<VkVertexInputBindingDescription> vertexInputBindingDescriptions{ };

        /**
         * @brief The vertex input attribute descriptions
         */
        std::vector<VkVertexInputAttributeDescription> vertexInputAttributeDescriptions{ };

         /**
         * @brief The push constant ranges to include in the pipeline layout
         */
        std::vector<VkPushConstantRange> pushConstantRanges{ };

        /**
         * @brief The descriptor set layouts to include in the pipeline layout
         */
        std::vector<IVulkanDescriptorSetLayout const *> descriptorSetLayouts{ };

        /**
         * @brief The pipeline vertex stage shader module
         */
        std::unique_ptr<IVulkanShaderModule> vertexShaderModule{ };

        /**
         * @brief The pipeline fragment stage shader module
         */
        std::unique_ptr<IVulkanShaderModule> fragmentShaderModule{ };
    };
}

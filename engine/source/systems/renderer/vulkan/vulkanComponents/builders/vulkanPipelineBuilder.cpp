#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanPipelineBuilder.hpp"

namespace siofraEngine::systems
{
    IVulkanPipelineBuilder& VulkanPipeline::Builder::withDevice(IVulkanDevice const * device) noexcept
    {
        this->device = device;
        return *this;
    }

    IVulkanPipelineBuilder& VulkanPipeline::Builder::withViewportExtents(VkExtent2D viewportExtents) noexcept
    {
        this->viewportExtents = viewportExtents;
        return *this;
    }

    IVulkanPipelineBuilder& VulkanPipeline::Builder::withRenderPass(IVulkanRenderPass const * renderPass) noexcept
    {
        this->renderPass = renderPass;
        return *this;
    }

    IVulkanPipelineBuilder& VulkanPipeline::Builder::withDescriptorSetLayouts(std::vector<IVulkanDescriptorSetLayout const *> descriptorSetLayouts) noexcept 
    {
        this->descriptorSetLayouts = descriptorSetLayouts;
        return *this;
    }
    
    IVulkanPipelineBuilder& VulkanPipeline::Builder::withVertexInputBindingDescription(uint32_t binding, uint32_t stride, VkVertexInputRate inputRate) noexcept
    {
        VkVertexInputBindingDescription bindingDescription{ };
        bindingDescription.binding = binding;
        bindingDescription.stride = stride;
        bindingDescription.inputRate = inputRate;
        vertexInputBindingDescriptions.push_back(bindingDescription);
        return *this;
    }

    IVulkanPipelineBuilder& VulkanPipeline::Builder::withVertexInputAttributeDescription(uint32_t binding, uint32_t location, VkFormat format, uint32_t offset) noexcept
    {
        VkVertexInputAttributeDescription attributeDescription{ };
        attributeDescription.binding = binding;
        attributeDescription.location = location;
        attributeDescription.format = format;
        attributeDescription.offset = offset;
        vertexInputAttributeDescriptions.push_back(attributeDescription);
        return *this;
    }

    IVulkanPipelineBuilder& VulkanPipeline::Builder::withPushConstantRange(VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size) noexcept
    {
        VkPushConstantRange pushConstantRange{ };
        pushConstantRange.stageFlags = stageFlags;
        pushConstantRange.offset = offset;
        pushConstantRange.size = size;
        pushConstantRanges.push_back(pushConstantRange);
        return *this;
    }

    IVulkanPipelineBuilder& VulkanPipeline::Builder::withVertexStage(std::unique_ptr<IVulkanShaderModule> shaderModule) noexcept
    {
        this->vertexShaderModule = std::move(shaderModule);
        return *this;
    }

    IVulkanPipelineBuilder& VulkanPipeline::Builder::withFragmentStage(std::unique_ptr<IVulkanShaderModule> shaderModule) noexcept
    {
        this->fragmentShaderModule = std::move(shaderModule);
        return *this;
    }

    std::unique_ptr<IVulkanPipeline> VulkanPipeline::Builder::build() const
    {
        VkPipelineVertexInputStateCreateInfo vertexInputCreateInfo{ };
        vertexInputCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertexInputCreateInfo.pVertexBindingDescriptions = vertexInputBindingDescriptions.data();
        vertexInputCreateInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(vertexInputBindingDescriptions.size());
        vertexInputCreateInfo.pVertexAttributeDescriptions = vertexInputAttributeDescriptions.data();
        vertexInputCreateInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInputAttributeDescriptions.size());

        VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo{ };
        inputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;

        VkViewport viewport{ };
        viewport.x = 0;
        viewport.y = 0;
        viewport.width = (float)viewportExtents.width;
        viewport.height = (float)viewportExtents.height;
        viewport.minDepth = 0;
        viewport.maxDepth = 1;

        VkRect2D scissor{ };
        scissor.offset = { 0, 0 };
        scissor.extent = viewportExtents;

        VkPipelineViewportStateCreateInfo viewportStateCreatInfo{ };
        viewportStateCreatInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportStateCreatInfo.pViewports = &viewport;
        viewportStateCreatInfo.viewportCount = 1;
        viewportStateCreatInfo.pScissors = &scissor;
        viewportStateCreatInfo.scissorCount = 1;

        /*
        std::vector<VkDynamicState> dynamicStateEnables;
        dynamicStateEnables.push_back(VK_DYNAMIC_STATE_VIEWPORT);
        dynamicStateEnables.push_back(VK_DYNAMIC_STATE_SCISSOR);

        VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = {};
        dynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamicStateCreateInfo.pDynamicStates = dynamicStateEnables.data();
        dynamicStateCreateInfo.dynamicStateCount = static_cast<uint32_t>(dynamicStateEnables.size());
        */

       VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo{ };
        rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
        rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
        rasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizationStateCreateInfo.lineWidth = 1.0f;
        rasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;

        VkPipelineMultisampleStateCreateInfo multisampleCreateInfo{ };
        multisampleCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampleCreateInfo.sampleShadingEnable = VK_FALSE;
        multisampleCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        VkPipelineColorBlendAttachmentState colourStateAttachment{ };
        colourStateAttachment.blendEnable = VK_TRUE;
        colourStateAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        colourStateAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colourStateAttachment.colorBlendOp = VK_BLEND_OP_ADD;
        colourStateAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        colourStateAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        colourStateAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
        colourStateAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT |
            VK_COLOR_COMPONENT_G_BIT |
            VK_COLOR_COMPONENT_B_BIT |
            VK_COLOR_COMPONENT_A_BIT;

        VkPipelineColorBlendStateCreateInfo colourBlendingCreateInfo{ };
        colourBlendingCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colourBlendingCreateInfo.logicOpEnable = VK_FALSE;
        colourBlendingCreateInfo.attachmentCount = 1;
        colourBlendingCreateInfo.pAttachments = &colourStateAttachment;

        std::vector<VkDescriptorSetLayout> descriptorSetLayoutHandles{ };
        for(auto const & descriptorSetLayout : descriptorSetLayouts)
        {
            descriptorSetLayoutHandles.push_back(descriptorSetLayout->getDescriptorSetLayout());
        }
        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{ };
        pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutCreateInfo.pSetLayouts = descriptorSetLayoutHandles.data();
        pipelineLayoutCreateInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayoutHandles.size());
        pipelineLayoutCreateInfo.pushConstantRangeCount = static_cast<uint32_t>(pushConstantRanges.size());
        pipelineLayoutCreateInfo.pPushConstantRanges = pushConstantRanges.data();

        VkPipelineLayout pipelineLayout{ VK_NULL_HANDLE };
        if (vkCreatePipelineLayout(device->getLogicalDevice(), &pipelineLayoutCreateInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create pipeline layout");
        }

        VkPipelineDepthStencilStateCreateInfo depthStencilCreateInfo{ };
        depthStencilCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        depthStencilCreateInfo.depthTestEnable = VK_TRUE;
        depthStencilCreateInfo.depthWriteEnable = VK_TRUE;
        depthStencilCreateInfo.depthCompareOp = VK_COMPARE_OP_LESS;
        depthStencilCreateInfo.depthBoundsTestEnable = VK_FALSE;
        depthStencilCreateInfo.stencilTestEnable = VK_FALSE;

        std::vector<VkPipelineShaderStageCreateInfo> shaderStages{ };
        if(vertexShaderModule)
        {
            VkPipelineShaderStageCreateInfo vertexShaderCreateInfo = {};
			vertexShaderCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			vertexShaderCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
			vertexShaderCreateInfo.module = vertexShaderModule->getShaderModule();
			vertexShaderCreateInfo.pName = "main";
            shaderStages.push_back(vertexShaderCreateInfo);
        }

        if(fragmentShaderModule)
        {
            VkPipelineShaderStageCreateInfo vertexShaderCreateInfo = {};
			vertexShaderCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			vertexShaderCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
			vertexShaderCreateInfo.module = fragmentShaderModule->getShaderModule();
			vertexShaderCreateInfo.pName = "main";
			shaderStages.push_back(vertexShaderCreateInfo);
        }

        VkGraphicsPipelineCreateInfo pipelineCreateInfo = {};
        pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineCreateInfo.pStages = shaderStages.data();
        pipelineCreateInfo.stageCount = static_cast<uint32_t>(shaderStages.size());
        pipelineCreateInfo.pVertexInputState = &vertexInputCreateInfo;
        pipelineCreateInfo.pInputAssemblyState = &inputAssemblyStateCreateInfo;
        pipelineCreateInfo.pViewportState = &viewportStateCreatInfo;
        pipelineCreateInfo.pRasterizationState = &rasterizationStateCreateInfo;
        pipelineCreateInfo.pMultisampleState = &multisampleCreateInfo;
        pipelineCreateInfo.pColorBlendState = &colourBlendingCreateInfo;
        pipelineCreateInfo.pDepthStencilState = &depthStencilCreateInfo;
        pipelineCreateInfo.pDynamicState = nullptr;
        pipelineCreateInfo.layout = pipelineLayout;
        pipelineCreateInfo.renderPass = renderPass->getRenderPass();
        pipelineCreateInfo.subpass = 0;
        pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
        pipelineCreateInfo.basePipelineIndex = -1;

        VkPipeline pipeline{ VK_NULL_HANDLE };
        if (vkCreateGraphicsPipelines(device->getLogicalDevice(), VK_NULL_HANDLE, 1, &pipelineCreateInfo, nullptr, &pipeline) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create pipeline");
        }

        return std::make_unique<VulkanPipeline>(pipeline, pipelineLayout, device);
    }
}

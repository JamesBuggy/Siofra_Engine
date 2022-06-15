#include "systems/renderer/vulkan/vulkanComponents/vulkanPipeline.hpp"

namespace siofraEngine::systems
{
    VulkanPipeline::VulkanPipeline(VkPipeline pipeline, VkPipelineLayout pipelineLayout, IVulkanDevice const * device) :
        pipeline{pipeline},
        pipelineLayout{pipelineLayout},
        device{device}
    {

    }

    VulkanPipeline::VulkanPipeline(VulkanPipeline &&other) noexcept :
        pipeline{other.pipeline},
        pipelineLayout{other.pipelineLayout},
        device{other.device}
    {
        other.pipeline = VK_NULL_HANDLE;
        other.pipelineLayout = VK_NULL_HANDLE;
        other.device = nullptr;
    }

    VulkanPipeline::~VulkanPipeline()
    {
        auto logicalDevice = device->getLogicalDevice();
        vkDestroyPipeline(logicalDevice, pipeline, nullptr);
		vkDestroyPipelineLayout(logicalDevice, pipelineLayout, nullptr);
    }

    VulkanPipeline& VulkanPipeline::operator=(VulkanPipeline &&other) noexcept
    {
        pipeline = other.pipeline;
        pipelineLayout = other.pipelineLayout;
        device = other.device;
        other.pipeline = VK_NULL_HANDLE;
        other.pipelineLayout = VK_NULL_HANDLE;
        other.device = nullptr;
        return *this;
    }

    VulkanPipeline::operator bool() const noexcept
    {
        return pipeline != VK_NULL_HANDLE &&
            pipelineLayout != VK_NULL_HANDLE;
    }

    VkPipeline VulkanPipeline::getPipeline() const noexcept
    {
        return pipeline;
    }

    VkPipelineLayout VulkanPipeline::getPipelineLayout() const noexcept
    {
        return pipelineLayout;
    }

    void VulkanPipeline::bind(IVulkanCommandBuffer const * commandBuffer, VkPipelineBindPoint pipelineBindPoint) const
    {
        vkCmdBindPipeline(commandBuffer->getCommandBuffer(), pipelineBindPoint, pipeline);
    }
}

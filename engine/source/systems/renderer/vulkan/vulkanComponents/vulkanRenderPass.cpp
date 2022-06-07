#include "systems/renderer/vulkan/vulkanComponents/vulkanRenderPass.hpp"

namespace siofraEngine::systems
{
    VulkanRenderPass::VulkanRenderPass(VkRenderPass renderPass, VkOffset2D renderAreaOffset, VkExtent2D renderAreaExtents, std::vector<VkClearValue> clearValues, std::vector<std::unique_ptr<IVulkanFramebuffer>> framebuffers, IVulkanDevice const * device) :
        renderPass{renderPass},
        renderAreaOffset{renderAreaOffset},
        renderAreaExtents{renderAreaExtents},
        clearValues{std::move(clearValues)},
        framebuffers{std::move(framebuffers)},
        device{device}
    {

    }

    VulkanRenderPass::VulkanRenderPass(VulkanRenderPass &&other) noexcept :
        renderPass{other.renderPass},
        renderAreaOffset{other.renderAreaOffset},
        renderAreaExtents{other.renderAreaExtents},
        clearValues{std::move(other.clearValues)},
        framebuffers{std::move(other.framebuffers)},
        device{other.device}
    {
        other.renderPass = VK_NULL_HANDLE;
        other.renderAreaOffset = { 0, 0 };
        other.renderAreaExtents = { 0, 0 };
        other.device = nullptr;
    }

    VulkanRenderPass::~VulkanRenderPass()
    {
        vkDestroyRenderPass(device->getLogicalDevice(), renderPass, nullptr);
    }

    VulkanRenderPass& VulkanRenderPass::operator=(VulkanRenderPass &&other) noexcept
    {
        renderPass = other.renderPass;
        renderAreaOffset = other.renderAreaOffset;
        renderAreaExtents = other.renderAreaExtents;
        clearValues = std::move(other.clearValues);
        framebuffers = std::move(other.framebuffers);
        device = other.device;
        other.renderPass = VK_NULL_HANDLE;
        other.renderAreaOffset = { 0, 0 };
        other.renderAreaExtents = { 0, 0 };
        other.device = nullptr;
        return *this;
    }

    VulkanRenderPass::operator bool() const noexcept
    {
        return renderPass != VK_NULL_HANDLE;
    }

    VkRenderPass VulkanRenderPass::getRenderPass() const noexcept
    {
        return renderPass;
    }

    std::vector<std::unique_ptr<IVulkanFramebuffer>> const & VulkanRenderPass::getFramebuffers() const noexcept
    {
        return framebuffers;
    }

    void VulkanRenderPass::begin(IVulkanCommandBuffer const * commandBuffer, uint32_t framebufferIndex) const
    {
        VkRenderPassBeginInfo renderPassBeginInfo = {};
        renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassBeginInfo.renderPass = renderPass;
        renderPassBeginInfo.renderArea.offset = renderAreaOffset;
        renderPassBeginInfo.renderArea.extent = renderAreaExtents;
        renderPassBeginInfo.pClearValues = clearValues.data();
        renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassBeginInfo.framebuffer = framebuffers[framebufferIndex]->getFramebuffer();

        vkCmdBeginRenderPass(commandBuffer->getCommandBuffer(), &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
    }

     void VulkanRenderPass::end(IVulkanCommandBuffer const * commandBuffer) const
     {
        vkCmdEndRenderPass(commandBuffer->getCommandBuffer());
     }
}

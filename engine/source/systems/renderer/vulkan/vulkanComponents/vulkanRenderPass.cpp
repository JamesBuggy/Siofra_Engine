#include "systems/renderer/vulkan/vulkanComponents/vulkanRenderPass.hpp"

namespace siofraEngine::systems
{
    VulkanRenderPass::VulkanRenderPass(VkRenderPass renderPass, VkOffset2D renderAreaOffset, VkExtent2D renderAreaExtents, IVulkanDevice const * device) :
        renderPass{renderPass},
        renderAreaOffset{renderAreaOffset},
        renderAreaExtents{renderAreaExtents},
        device{device}
    {

    }

    VulkanRenderPass::VulkanRenderPass(VulkanRenderPass &&other) noexcept :
        renderPass{other.renderPass},
        renderAreaOffset{other.renderAreaOffset},
        renderAreaExtents{other.renderAreaExtents},
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
}

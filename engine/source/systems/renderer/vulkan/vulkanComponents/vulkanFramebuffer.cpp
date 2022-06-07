#include "systems/renderer/vulkan/vulkanComponents/vulkanFramebuffer.hpp"

namespace siofraEngine::systems
{
    VulkanFramebuffer::VulkanFramebuffer(VkFramebuffer Framebuffer, IVulkanDevice const * device) :
        Framebuffer{Framebuffer},
        device{device}
    {

    }

    VulkanFramebuffer::VulkanFramebuffer(VulkanFramebuffer &&other) noexcept :
        Framebuffer{other.Framebuffer},
        device{other.device}
    {
        other.Framebuffer = VK_NULL_HANDLE;
        other.device = nullptr;
    }

    VulkanFramebuffer::~VulkanFramebuffer()
    {
        vkDestroyFramebuffer(device->getLogicalDevice(), Framebuffer, nullptr);
    }

    VulkanFramebuffer& VulkanFramebuffer::operator=(VulkanFramebuffer &&other) noexcept
    {
        Framebuffer = other.Framebuffer;
        device = other.device;
        other.Framebuffer = VK_NULL_HANDLE;
        other.device = nullptr;
        return *this;
    }

    VulkanFramebuffer::operator bool() const noexcept
    {
        return Framebuffer != VK_NULL_HANDLE;
    }

    VkFramebuffer VulkanFramebuffer::getFramebuffer() const noexcept
    {
        return Framebuffer;
    }
}

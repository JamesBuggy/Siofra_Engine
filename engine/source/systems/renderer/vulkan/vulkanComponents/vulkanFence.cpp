#include "systems/renderer/vulkan/vulkanComponents/vulkanFence.hpp"

namespace siofraEngine::systems
{
    VulkanFence::VulkanFence(VkFence fence, IVulkanDevice const * device) :
        fence{fence},
        device{device}
    {
        
    }

    VulkanFence::VulkanFence(VulkanFence &&other) noexcept :
        fence{other.fence},
        device{other.device}
    {
        other.fence = VK_NULL_HANDLE;
        other.device = nullptr;
    }

    VulkanFence::~VulkanFence()
    {
        vkDestroyFence(device->getLogicalDevice(), fence, nullptr);
    }

    VulkanFence& VulkanFence::operator=(VulkanFence &&other) noexcept
    {
        fence = other.fence;
        device = other.device;
        other.fence = VK_NULL_HANDLE;
        other.device = nullptr;
        return *this;
    }

    VulkanFence::operator bool() const noexcept
    {
        return fence != VK_NULL_HANDLE;
    }

    VkFence VulkanFence::getFence() const noexcept
    {
        return fence;
    }
}

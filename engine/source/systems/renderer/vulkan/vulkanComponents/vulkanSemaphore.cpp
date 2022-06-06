#include "systems/renderer/vulkan/vulkanComponents/vulkanSemaphore.hpp"

namespace siofraEngine::systems
{
    VulkanSemaphore::VulkanSemaphore(VkSemaphore semaphore, IVulkanDevice const * device) :
        semaphore{semaphore},
        device{device}
    {
        
    }

    VulkanSemaphore::VulkanSemaphore(VulkanSemaphore &&other) noexcept :
        semaphore{other.semaphore},
        device{other.device}
    {
        other.semaphore = VK_NULL_HANDLE;
        other.device = nullptr;
    }

    VulkanSemaphore::~VulkanSemaphore()
    {
        vkDestroySemaphore(device->getLogicalDevice(), semaphore, nullptr);
    }

    VulkanSemaphore& VulkanSemaphore::operator=(VulkanSemaphore &&other) noexcept
    {
        semaphore = other.semaphore;
        device = other.device;
        other.semaphore = VK_NULL_HANDLE;
        other.device = nullptr;
        return *this;
    }

    VulkanSemaphore::operator bool() const noexcept
    {
        return semaphore != VK_NULL_HANDLE;
    }

    VkSemaphore VulkanSemaphore::getSemaphore() const noexcept
    {
        return semaphore;
    }
}

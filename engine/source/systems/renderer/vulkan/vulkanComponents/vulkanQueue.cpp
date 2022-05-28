#include "systems/renderer/vulkan/vulkanComponents/vulkanQueue.hpp"

namespace siofraEngine::systems
{
    VulkanQueue::VulkanQueue(VkQueue queue) :
        queue(queue)
    {

    }

    VulkanQueue::VulkanQueue(VulkanQueue &&other) noexcept :
        queue(other.queue)
    {
        other.queue = VK_NULL_HANDLE;
    }

    VulkanQueue& VulkanQueue::operator=(VulkanQueue &&other) noexcept
    {
        queue = other.queue;
        other.queue = VK_NULL_HANDLE;
        return *this;
    }

    VulkanQueue::operator bool() const noexcept
    {
        return queue != VK_NULL_HANDLE;
    }

    VkQueue VulkanQueue::getQueue() const noexcept
    {
        return queue;
    }
}

#include "systems/renderer/vulkan/vulkanComponents/vulkanQueue.hpp"

namespace siofraEngine::systems
{
    VulkanQueue::VulkanQueue(VkQueue queue, uint32_t familyIndex) :
        queue(queue),
        familyIndex(familyIndex)
    {

    }

    VulkanQueue::VulkanQueue(VulkanQueue &&other) noexcept :
        queue(other.queue),
        familyIndex(other.familyIndex)
    {
        other.queue = VK_NULL_HANDLE;
    }

    VulkanQueue& VulkanQueue::operator=(VulkanQueue &&other) noexcept
    {
        queue = other.queue;
        familyIndex = other.familyIndex;
        other.queue = VK_NULL_HANDLE;
        other.familyIndex = -1;
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

    uint32_t VulkanQueue::getFamilyIndex() const noexcept
    {
        return familyIndex;
    }
}

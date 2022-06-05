#include "systems/renderer/vulkan/vulkanComponents/vulkanCommandPool.hpp"

namespace siofraEngine::systems
{
    VulkanCommandPool::VulkanCommandPool(VkCommandPool commandPool, IVulkanDevice const * device) :
        commandPool{commandPool},
        device{device}
    {

    }

    VulkanCommandPool::VulkanCommandPool(VulkanCommandPool &&other) noexcept :
        commandPool{other.commandPool},
        device{other.device}
    {
        other.commandPool = VK_NULL_HANDLE;
        other.device = nullptr;
    }

    VulkanCommandPool& VulkanCommandPool::operator=(VulkanCommandPool &&other) noexcept
    {
        commandPool = other.commandPool;
        device = other.device;
        other.commandPool = VK_NULL_HANDLE;
        other.device = nullptr;
        return *this;
    }

    VulkanCommandPool::~VulkanCommandPool()
    {
        vkDestroyCommandPool(device->getLogicalDevice(), commandPool, nullptr);
    }

    VulkanCommandPool::operator bool() const noexcept
    {
        return commandPool != VK_NULL_HANDLE;
    }

    VkCommandPool VulkanCommandPool::getCommandPool() const noexcept
    {
        return commandPool;
    }
}

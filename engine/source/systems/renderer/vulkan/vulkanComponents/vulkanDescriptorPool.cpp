#include "systems/renderer/vulkan/vulkanComponents/vulkanDescriptorPool.hpp"

namespace siofraEngine::systems
{
    VulkanDescriptorPool::VulkanDescriptorPool(VkDescriptorPool descriptorPool, IVulkanDevice const * device) :
        descriptorPool{descriptorPool},
        device{device}
    {

    }

    VulkanDescriptorPool::VulkanDescriptorPool(VulkanDescriptorPool &&other) noexcept :
        descriptorPool{other.descriptorPool},
        device{other.device}
    {
        other.descriptorPool = VK_NULL_HANDLE;
        other.device = nullptr;
    }

    VulkanDescriptorPool::~VulkanDescriptorPool()
    {
        vkDestroyDescriptorPool(device->getLogicalDevice(), descriptorPool, nullptr);
    }

    VulkanDescriptorPool& VulkanDescriptorPool::operator=(VulkanDescriptorPool &&other) noexcept
    {
        descriptorPool = other.descriptorPool;
        device = other.device;
        other.descriptorPool = VK_NULL_HANDLE;
        other.device = nullptr;
        return *this;
    }

    VulkanDescriptorPool::operator bool() const noexcept
    {
        return descriptorPool != VK_NULL_HANDLE;
    }

    VkDescriptorPool VulkanDescriptorPool::getDescriptorPool() const noexcept
    {
        return descriptorPool;
    }
}

#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanQueueBuilder.hpp"

namespace siofraEngine::systems
{
    IVulkanQueueBuilder& VulkanQueue::Builder::withLogicalDevice(VkDevice logicalDevice) noexcept
    {
        this->logicalDevice = logicalDevice;
        return *this;
    }

    IVulkanQueueBuilder& VulkanQueue::Builder::withQueueFamilyIndex(std::uint32_t queueFamilyIndex) noexcept
    {
        this->queueFamilyIndex = queueFamilyIndex;
        return *this;
    }

    IVulkanQueueBuilder& VulkanQueue::Builder::withQueueIndex(std::uint32_t queueIndex) noexcept
    {
        this->queueIndex = queueIndex;
        return *this;
    }

    std::unique_ptr<IVulkanQueue> VulkanQueue::Builder::build() const
    {
        VkQueue queue = VK_NULL_HANDLE;
        if(queueFamilyIndex >= 0 && queueIndex >= 0)
        {
            vkGetDeviceQueue(logicalDevice, queueFamilyIndex, queueIndex, &queue);
        }
        
        return std::make_unique<VulkanQueue>(queue, queueFamilyIndex);
    }
}

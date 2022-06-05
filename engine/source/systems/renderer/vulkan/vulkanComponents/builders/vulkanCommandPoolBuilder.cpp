#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanCommandPoolBuilder.hpp"

namespace siofraEngine::systems
{
    IVulkanCommandPoolBuilder& VulkanCommandPool::Builder::withDevice(IVulkanDevice const * device) noexcept
    {
        this->device = device;
        return *this;
    }

    IVulkanCommandPoolBuilder& VulkanCommandPool::Builder::withFlags(VkCommandPoolCreateFlags flags) noexcept
    {
        this->flags = flags;
        return *this;
    }

    IVulkanCommandPoolBuilder& VulkanCommandPool::Builder::withQueueFamilyIndex(uint32_t queueFamilyIndex) noexcept
    {
        this->queueFamilyIndex = queueFamilyIndex;
        return *this;
    }

    std::unique_ptr<IVulkanCommandPool> VulkanCommandPool::Builder::build() const
    {
        VkCommandPoolCreateInfo poolInfo{ };
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = flags;
        poolInfo.queueFamilyIndex = queueFamilyIndex;

        VkCommandPool commandPool{ VK_NULL_HANDLE };
        if (vkCreateCommandPool(device->getLogicalDevice(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create command pool");
        }

        return std::make_unique<VulkanCommandPool>(commandPool, device);
    }
}

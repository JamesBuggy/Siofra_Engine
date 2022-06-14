#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanCommandBufferBuilder.hpp"

namespace siofraEngine::systems
{
    IVulkanCommandBufferBuilder& VulkanCommandBuffer::Builder::withDevice(IVulkanDevice const * device) noexcept
    {
        this->device = device;
        return *this;
    }

    IVulkanCommandBufferBuilder& VulkanCommandBuffer::Builder::withLevel(VkCommandBufferLevel level) noexcept
    {
        this->level = level;
        return *this;
    }

    IVulkanCommandBufferBuilder& VulkanCommandBuffer::Builder::withCommandPool(IVulkanCommandPool const * commandPool) noexcept
    {
        this->commandPool = commandPool;
        return *this;
    }

    std::vector<std::unique_ptr<IVulkanCommandBuffer>> VulkanCommandBuffer::Builder::build(uint32_t count) const
    {
        VkCommandBufferAllocateInfo commandBufferAllocInfo{ };
        commandBufferAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        commandBufferAllocInfo.commandPool = commandPool->getCommandPool();
        commandBufferAllocInfo.level = level;
        commandBufferAllocInfo.commandBufferCount = count;

        std::vector<VkCommandBuffer> commandBufferHandles(count, VK_NULL_HANDLE);
        if (vkAllocateCommandBuffers(device->getLogicalDevice(), &commandBufferAllocInfo, commandBufferHandles.data()) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to allocate command buffer(s)");
        }

        std::vector<std::unique_ptr<IVulkanCommandBuffer>> commandBuffers(count);
        for(size_t i = 0; i < count; ++i)
        {
            commandBuffers[i] = std::make_unique<VulkanCommandBuffer>(commandBufferHandles[i]);
        }

        return commandBuffers;
    }

    std::unique_ptr<IVulkanCommandBuffer> VulkanCommandBuffer::Builder::build() const
    {
        VkCommandBufferAllocateInfo commandBufferAllocInfo{ };
        commandBufferAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        commandBufferAllocInfo.commandPool = commandPool->getCommandPool();
        commandBufferAllocInfo.level = level;
        commandBufferAllocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer{ VK_NULL_HANDLE };
        if (vkAllocateCommandBuffers(device->getLogicalDevice(), &commandBufferAllocInfo, &commandBuffer) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to allocate command buffer(s)");
        }

        return std::make_unique<VulkanCommandBuffer>(commandBuffer);
    }
}

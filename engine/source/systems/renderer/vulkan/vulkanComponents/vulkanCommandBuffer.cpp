#include "systems/renderer/vulkan/vulkanComponents/vulkanCommandBuffer.hpp"

namespace siofraEngine::systems
{
    VulkanCommandBuffer::VulkanCommandBuffer(VkCommandBuffer commandBuffer) :
        commandBuffer{commandBuffer}
    {
        
    }

    VulkanCommandBuffer::VulkanCommandBuffer(VulkanCommandBuffer &&other) noexcept :
        commandBuffer{other.commandBuffer}
    {
        other.commandBuffer = VK_NULL_HANDLE;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::operator=(VulkanCommandBuffer &&other) noexcept
    {
        commandBuffer = other.commandBuffer;
        other.commandBuffer = VK_NULL_HANDLE;
        return *this;
    }

    VulkanCommandBuffer::operator bool() const noexcept
    {
        return commandBuffer != VK_NULL_HANDLE;
    }

    VkCommandBuffer VulkanCommandBuffer::getCommandBuffer() const noexcept
    {
        return commandBuffer;
    }
}

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

    void VulkanCommandBuffer::begin(VkCommandBufferUsageFlags flags) const
    {
        VkCommandBufferBeginInfo commandBufferBeginInfo{ };
        commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        commandBufferBeginInfo.flags = flags;

        if (vkBeginCommandBuffer(commandBuffer, &commandBufferBeginInfo) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to start recording on the command buffer");
        }
    }

    void VulkanCommandBuffer::end() const
    {
        if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to stop recording on the command buffer");
        }
    }
}

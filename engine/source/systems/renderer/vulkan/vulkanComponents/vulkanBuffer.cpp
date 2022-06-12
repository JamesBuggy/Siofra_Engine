#include "systems/renderer/vulkan/vulkanComponents/vulkanBuffer.hpp"

namespace siofraEngine::systems
{
    VulkanBuffer::VulkanBuffer(VkBuffer buffer, VkDeviceMemory bufferMemory, IVulkanDevice const * device) :
        buffer{buffer},
        bufferMemory{bufferMemory},
        device{device}
    {

    }

    VulkanBuffer::VulkanBuffer(VulkanBuffer &&other) noexcept :
        buffer{other.buffer},
        bufferMemory{other.bufferMemory},
        device{other.device}
    {
        other.buffer = VK_NULL_HANDLE;
        other.bufferMemory = VK_NULL_HANDLE;
        other.device = nullptr;
    }

    VulkanBuffer::~VulkanBuffer()
    {
        auto logicalDevice = device->getLogicalDevice();
        vkDestroyBuffer(logicalDevice, buffer, nullptr);
        vkFreeMemory(logicalDevice, bufferMemory, nullptr);
    }

    VulkanBuffer& VulkanBuffer::operator=(VulkanBuffer &&other) noexcept
    {
        buffer = other.buffer;
        bufferMemory = other.bufferMemory;
        device = other.device;
        other.buffer = VK_NULL_HANDLE;
        other.bufferMemory = VK_NULL_HANDLE;
        other.device = nullptr;
        return *this;
    }

    VulkanBuffer::operator bool() const noexcept
    {
        return buffer != VK_NULL_HANDLE;
    }

    VkBuffer VulkanBuffer::getBuffer() const noexcept
    {
        return buffer;
    }
}

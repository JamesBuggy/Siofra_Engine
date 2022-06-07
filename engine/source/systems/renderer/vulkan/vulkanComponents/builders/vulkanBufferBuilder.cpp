#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanBufferBuilder.hpp"

namespace siofraEngine::systems
{
    IVulkanBufferBuilder& VulkanBuffer::Builder::withDevice(IVulkanDevice const * device) noexcept
    {
        this->device = device;
        return *this;
    }

    IVulkanBufferBuilder& VulkanBuffer::Builder::withBufferSize(VkDeviceSize bufferSize) noexcept
    {
        this->bufferSize = bufferSize;
        return *this;
    }

    IVulkanBufferBuilder& VulkanBuffer::Builder::withBufferUsageFlags(VkBufferUsageFlags bufferUsageFlags) noexcept
    {
        this->bufferUsageFlags = bufferUsageFlags;
        return *this;
    }

    IVulkanBufferBuilder& VulkanBuffer::Builder::withMemoryPropertyFlags(VkMemoryPropertyFlags memoryPropertyFlags) noexcept
    {
        this->memoryPropertyFlags = memoryPropertyFlags;
        return *this;
    }

    std::unique_ptr<IVulkanBuffer> VulkanBuffer::Builder::build() const
    {
        VkDevice logicalDevice = device->getLogicalDevice();

        VkBufferCreateInfo bufferInfo{ };
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = bufferSize;
        bufferInfo.usage = bufferUsageFlags;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        VkBuffer buffer{ VK_NULL_HANDLE };
        if (vkCreateBuffer(logicalDevice, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create buffer");
        }

        VkMemoryRequirements memoryRequirments{ };
        vkGetBufferMemoryRequirements(logicalDevice, buffer, &memoryRequirments);

        VkMemoryAllocateInfo memoryAllocInfo{ };
        memoryAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memoryAllocInfo.allocationSize = memoryRequirments.size;
        memoryAllocInfo.memoryTypeIndex = findMemoryTypeIndex(device, memoryRequirments.memoryTypeBits, memoryPropertyFlags);

        VkDeviceMemory bufferMemory{ VK_NULL_HANDLE };
        if (vkAllocateMemory(logicalDevice, &memoryAllocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to allocate buffer memory");
        }

        vkBindBufferMemory(logicalDevice, buffer, bufferMemory, 0);

        return std::make_unique<VulkanBuffer>(buffer, bufferMemory, device);
    }

    uint32_t VulkanBuffer::Builder::findMemoryTypeIndex(IVulkanDevice const * device, uint32_t allowedTypes, VkMemoryPropertyFlags properties) const
    {
        VkPhysicalDeviceMemoryProperties memoryProperties{ };
        vkGetPhysicalDeviceMemoryProperties(device->getPhysicalDevice(), &memoryProperties);

        for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
        {
            if ((allowedTypes & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
            {
                return i;
            }
        }

        throw std::runtime_error("Failed to find buffer memory type index");
    }
}

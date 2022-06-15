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

    void VulkanBuffer::update(void const * data, size_t size) const
    {
        void * destination;
        auto logicalDevice = device->getLogicalDevice();
        vkMapMemory(logicalDevice, bufferMemory, 0, size, 0, &destination);
        memcpy(destination, data, size);
        vkUnmapMemory(logicalDevice, bufferMemory);
    }

    void VulkanBuffer::copyToImage(IVulkanCommandBuffer const * commandBuffer, IVulkanQueue const * queue, IVulkanImage const * image, uint32_t width, uint32_t height) const
    {
        commandBuffer->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

        VkBufferImageCopy imageRegion{ };
        imageRegion.bufferOffset = 0;
        imageRegion.bufferRowLength = 0;
        imageRegion.bufferImageHeight = 0;
        imageRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageRegion.imageSubresource.mipLevel = 0;
        imageRegion.imageSubresource.baseArrayLayer = 0;
        imageRegion.imageSubresource.layerCount = 1;
        imageRegion.imageOffset.x = 0;
        imageRegion.imageOffset.y = 0;
        imageRegion.imageOffset.z = 0;
        imageRegion.imageExtent.width = width;
        imageRegion.imageExtent.height = height;
        imageRegion.imageExtent.depth = 1;

        std::vector<VkBufferImageCopy> regions{
            imageRegion
        };

        vkCmdCopyBufferToImage(commandBuffer->getCommandBuffer(), buffer, image->getImage(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, static_cast<uint32_t>(regions.size()), regions.data());

        commandBuffer->end();

        queue->submit(commandBuffer);
        queue->waitIdle();
    }

    void VulkanBuffer::copyToBuffer(IVulkanCommandBuffer const * commandBuffer, IVulkanQueue const * queue, IVulkanBuffer const * destinationBuffer, VkDeviceSize bytes) const
    {
        commandBuffer->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

        VkBufferCopy bufferCopyRegion = {};
        bufferCopyRegion.srcOffset = 0;
        bufferCopyRegion.dstOffset = 0;
        bufferCopyRegion.size = bytes;

        std::vector<VkBufferCopy> bufferCopyRegions = {
            bufferCopyRegion
        };

        vkCmdCopyBuffer(commandBuffer->getCommandBuffer(), buffer, destinationBuffer->getBuffer(), static_cast<uint32_t>(bufferCopyRegions.size()), bufferCopyRegions.data());

        commandBuffer->end();

        queue->submit(commandBuffer);
        queue->waitIdle();
    }
}

#include "systems/renderer/vulkan/vulkanComponents/vulkanImage.hpp"

namespace siofraEngine::systems
{
    VulkanImage::VulkanImage(VkImage image, VkImageView imageView, VkDeviceMemory imageMemory, bool managedImage, IVulkanDevice const * device) :
        image{image},
        imageView{imageView},
        imageMemory{imageMemory},
        managedImage{managedImage},
        device{device}
    {

    }

    VulkanImage::VulkanImage(VulkanImage &&other) noexcept :
        image{other.image},
        imageView{other.imageView},
        imageMemory{other.imageMemory},
        managedImage{other.managedImage},
        device{other.device}
    {
        other.image = VK_NULL_HANDLE;
        other.imageView = VK_NULL_HANDLE;
        other.imageMemory = VK_NULL_HANDLE;
        other.managedImage = false;
        other.device = nullptr;
    }

    VulkanImage::~VulkanImage()
    {
        auto logicalDevice = device->getLogicalDevice();
        vkDestroyImageView(logicalDevice, imageView, nullptr);
        if(!managedImage)
        {
            vkDestroyImage(logicalDevice, image, nullptr);
            vkFreeMemory(logicalDevice, imageMemory, nullptr);
        }
    }

    VulkanImage& VulkanImage::operator=(VulkanImage &&other) noexcept
    {
        image = other.image;
        imageView = other.imageView;
        imageMemory = other.imageMemory;
        managedImage = other.managedImage;
        device = other.device;
        other.image = VK_NULL_HANDLE;
        other.imageView = VK_NULL_HANDLE;
        other.imageMemory = VK_NULL_HANDLE;
        other.managedImage = false;
        other.device = nullptr;
        return *this;
    }

    VulkanImage::operator bool() const noexcept
    {
        return image != VK_NULL_HANDLE &&
            imageView != VK_NULL_HANDLE &&
            imageMemory != VK_NULL_HANDLE;
    }

    VkImageView VulkanImage::getImageView() const noexcept
    {
        return imageView;
    }

    VkImage VulkanImage::getImage() const noexcept
    {
        return image;
    }

    void VulkanImage::transitionImageLayout(IVulkanCommandBuffer const * commandBuffer, IVulkanQueue const * queue, VkImageLayout oldLayout, VkImageLayout newLayout) const
    {
        commandBuffer->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

        VkImageMemoryBarrier imageMemoryBarrier{ };
        imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        imageMemoryBarrier.oldLayout = oldLayout;
        imageMemoryBarrier.newLayout = newLayout;
        imageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        imageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        imageMemoryBarrier.image = image;
        imageMemoryBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageMemoryBarrier.subresourceRange.baseArrayLayer = 0;
        imageMemoryBarrier.subresourceRange.baseMipLevel = 0;
        imageMemoryBarrier.subresourceRange.layerCount = 1;
        imageMemoryBarrier.subresourceRange.levelCount = 1;

        VkPipelineStageFlags srcStage;
        VkPipelineStageFlags dstStage;

        if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
        {
            imageMemoryBarrier.srcAccessMask = 0;
            imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

            srcStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            dstStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        }
        else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
        {
            imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            imageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

            srcStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
            dstStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        }

        std::vector<VkImageMemoryBarrier> imageMemoryBarriers{
            imageMemoryBarrier
        };

        VkCommandBuffer commandBufferHandle = commandBuffer->getCommandBuffer();
        vkCmdPipelineBarrier(commandBufferHandle, srcStage, dstStage, 0, 0, nullptr, 0, nullptr, static_cast<uint32_t>(imageMemoryBarriers.size()), imageMemoryBarriers.data());

        commandBuffer->end();

        queue->submit(commandBuffer);
        queue->waitIdle();
    }
}

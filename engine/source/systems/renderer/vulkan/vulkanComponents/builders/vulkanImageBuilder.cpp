#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanImageBuilder.hpp"

namespace siofraEngine::systems
{
    IVulkanImageBuilder& VulkanImage::Builder::withDevice(IVulkanDevice const * device) noexcept
    {
        this->device = device;
        return *this;
    }

    IVulkanImageBuilder& VulkanImage::Builder::withExtents(uint32_t width, uint32_t height) noexcept
    {
        this->width = width;
        this->height = height;
        return *this;
    }

    IVulkanImageBuilder& VulkanImage::Builder::withFormat(VkFormat format) noexcept
    {
        this->format = format;
        return *this;
    }

    IVulkanImageBuilder& VulkanImage::Builder::withTiling(VkImageTiling tiling) noexcept
    {
        this->tiling = tiling;
        return *this;
    }

    IVulkanImageBuilder& VulkanImage::Builder::withUsageFlags(VkImageUsageFlags usageFlags) noexcept
    {
        this->usageFlags = usageFlags;
        return *this;
    }

    IVulkanImageBuilder& VulkanImage::Builder::withMemoryPropertyFlags(VkMemoryPropertyFlags memoryPropertyFlags) noexcept
    {
        this->memoryPropertyFlags = memoryPropertyFlags;
        return *this;
    }

    IVulkanImageBuilder& VulkanImage::Builder::withAspectFlags(VkImageAspectFlags aspectFlags) noexcept
    {
        this->aspectFlags = aspectFlags;
        return *this;
    }

    IVulkanImageBuilder& VulkanImage::Builder::withExistingImageHandle(VkImage image) noexcept
    {
        this->existingImage = image;
        return *this;
    }

    std::unique_ptr<IVulkanImage> VulkanImage::Builder::build() const
    {
        VkImage image{ VK_NULL_HANDLE };
        VkImageView imageView{ VK_NULL_HANDLE };
        VkDeviceMemory imageMemory{ VK_NULL_HANDLE };
        bool managedImage{ false };

        if (existingImage != VK_NULL_HANDLE)
        {
            image = existingImage;
            managedImage = true;
        }
        else
        {
            if (!createImage(device, width, height, format, tiling, usageFlags, image))
            {
                throw std::runtime_error("Failed to create an image");
            }

            if (!allocateImageMemory(device, image, memoryPropertyFlags, imageMemory))
            {
                throw std::runtime_error("Failed to allocate image memory");
            }
        }

        if(!createImageView(device, image, format, aspectFlags, imageView))
        {
            throw std::runtime_error("Failed to create an image view");
        }

        return std::make_unique<VulkanImage>(image, imageView, imageMemory, managedImage, device);
    }

    bool VulkanImage::Builder::createImage(IVulkanDevice const * device, uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usageFlags, VkImage& image) const
    {
        VkImageCreateInfo imageCreateInfo{ };
        imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
        imageCreateInfo.extent.width = width;
        imageCreateInfo.extent.height = height;
        imageCreateInfo.extent.depth = 1;
        imageCreateInfo.mipLevels = 1;
        imageCreateInfo.arrayLayers = 1;
        imageCreateInfo.format = format;
        imageCreateInfo.tiling = tiling;
        imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageCreateInfo.usage = usageFlags;
        imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        return vkCreateImage(device->getLogicalDevice(), &imageCreateInfo, nullptr, &image) == VK_SUCCESS;
    }

    bool VulkanImage::Builder::createImageView(IVulkanDevice const * device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VkImageView& imageView) const
    {
        VkImageViewCreateInfo viewCreateInfo{ };
        viewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewCreateInfo.image = image;
        viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewCreateInfo.format = format;
        viewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewCreateInfo.subresourceRange.aspectMask = aspectFlags;
        viewCreateInfo.subresourceRange.baseMipLevel = 0;
        viewCreateInfo.subresourceRange.levelCount = 1;
        viewCreateInfo.subresourceRange.baseArrayLayer = 0;
        viewCreateInfo.subresourceRange.layerCount = 1;

        return vkCreateImageView(device->getLogicalDevice(), &viewCreateInfo, nullptr, &imageView) == VK_SUCCESS;
    }

    bool VulkanImage::Builder::allocateImageMemory(IVulkanDevice const * device, VkImage image, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceMemory& imageMemory) const
    {
        VkMemoryRequirements memoryRequirements{ };
        vkGetImageMemoryRequirements(device->getLogicalDevice(), image, &memoryRequirements);

        VkMemoryAllocateInfo memoryAllocInfo{ };
        memoryAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memoryAllocInfo.allocationSize = memoryRequirements.size;
        memoryAllocInfo.memoryTypeIndex = findMemoryTypeIndex(device, memoryRequirements.memoryTypeBits, memoryPropertyFlags);

        return vkAllocateMemory(device->getLogicalDevice(), &memoryAllocInfo, nullptr, &imageMemory) == VK_SUCCESS &&
            vkBindImageMemory(device->getLogicalDevice(), image, imageMemory, 0) == VK_SUCCESS;
    }

    uint32_t VulkanImage::Builder::findMemoryTypeIndex(IVulkanDevice const * device, uint32_t allowedTypes, VkMemoryPropertyFlags properties) const
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

        throw std::runtime_error("Failed to find image memory type index");
    }
}

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
}

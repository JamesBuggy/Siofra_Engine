#include "systems/renderer/vulkan/vulkanComponents/vulkanSwapchain.hpp"

namespace siofraEngine::systems
{
    VulkanSwapchain::VulkanSwapchain(VkSwapchainKHR swapchain, VkFormat swapchainImageFormat, VkFormat depthAttachmentFormat, VkExtent2D swapchainExtents, std::vector<std::unique_ptr<IVulkanImage>> swapChainImages, std::unique_ptr<IVulkanImage> depthAttachment, IVulkanDevice const * device) :
        swapchain{swapchain},
        swapchainImageFormat{swapchainImageFormat},
        depthAttachmentFormat{depthAttachmentFormat},
        swapchainExtents{swapchainExtents},
        swapChainImages{std::move(swapChainImages)},
        depthAttachment{std::move(depthAttachment)},
        device{device}
    {

    }

    VulkanSwapchain::VulkanSwapchain(VulkanSwapchain &&other) noexcept :
        swapchain{other.swapchain},
        swapchainImageFormat{other.swapchainImageFormat},
        depthAttachmentFormat{other.depthAttachmentFormat},
        swapchainExtents{other.swapchainExtents},
        swapChainImages{std::move(other.swapChainImages)},
        depthAttachment{std::move(other.depthAttachment)},
        device{other.device}
    {
        other.swapchain = VK_NULL_HANDLE;
        other.swapchainImageFormat = VK_FORMAT_UNDEFINED;
        other.depthAttachmentFormat = VK_FORMAT_UNDEFINED;
        other.swapchainExtents = {0, 0};
        other.device = nullptr;
    }

    VulkanSwapchain::~VulkanSwapchain()
    {
        vkDestroySwapchainKHR(device->getLogicalDevice(), swapchain, nullptr);
    }

    VulkanSwapchain& VulkanSwapchain::operator=(VulkanSwapchain &&other) noexcept
    {
        swapchain = other.swapchain;
        swapchainImageFormat = other.swapchainImageFormat;
        depthAttachmentFormat = other.depthAttachmentFormat;
        swapchainExtents = other.swapchainExtents;
        device = other.device;
        swapChainImages = std::move(other.swapChainImages);
        depthAttachment = std::move(other.depthAttachment);
        other.swapchain = VK_NULL_HANDLE;
        other.swapchainImageFormat = VK_FORMAT_UNDEFINED;
        other.depthAttachmentFormat = VK_FORMAT_UNDEFINED;
        other.swapchainExtents = {0, 0};
        other.device = nullptr;
        return *this;
    }

    VulkanSwapchain::operator bool() const noexcept
    {
        return swapchain != VK_NULL_HANDLE &&
            swapchainImageFormat != VK_FORMAT_UNDEFINED &&
            depthAttachmentFormat != VK_FORMAT_UNDEFINED &&
            swapchainExtents.width > 0 &&
            swapchainExtents.height > 0 &&
            swapChainImages.size() > 0 &&
            depthAttachment;
    }

    VkSwapchainKHR VulkanSwapchain::getSwapchain() const noexcept
    {
        return swapchain;
    }

    VkFormat VulkanSwapchain::getImageFormat() const noexcept
    {
        return swapchainImageFormat;
    }

    VkFormat VulkanSwapchain::getDepthAttachmentFormat() const noexcept 
    {
        return depthAttachmentFormat;
    }

    VkExtent2D VulkanSwapchain::getExtents() const noexcept
    {
        return swapchainExtents;
    }

    std::vector<std::unique_ptr<IVulkanImage>> const & VulkanSwapchain::getSwapchainImages() const noexcept
    {
        return swapChainImages;
    }

    std::unique_ptr<IVulkanImage> const & VulkanSwapchain::getDepthAttachment() const noexcept
    {
        return depthAttachment;
    }

    uint32_t VulkanSwapchain::getMaxFramesInFlight() const noexcept
    {
        return swapChainImages.size() - 1;
    }

    uint32_t VulkanSwapchain::acquireNextImage(IVulkanSemaphore const * semaphore) const
    {
        VkSemaphore semaphoreHandle = semaphore->getSemaphore();

        uint32_t imageIndex{ };
        if(vkAcquireNextImageKHR(device->getLogicalDevice(), swapchain, std::numeric_limits<uint64_t>::max(), semaphoreHandle, VK_NULL_HANDLE, &imageIndex) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to acquire next swapchain image");
        }
        return imageIndex;
    }
}

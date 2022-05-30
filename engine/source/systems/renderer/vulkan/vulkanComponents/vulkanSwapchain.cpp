#include "systems/renderer/vulkan/vulkanComponents/vulkanSwapchain.hpp"

namespace siofraEngine::systems
{
    VulkanSwapchain::VulkanSwapchain(VkSwapchainKHR swapchain, VkFormat swapchainImageFormat, VkExtent2D swapchainExtents, std::vector<std::unique_ptr<IVulkanImage>> swapChainImages, IVulkanDevice const * device) :
        swapchain{swapchain},
        swapchainImageFormat{swapchainImageFormat},
        swapchainExtents{swapchainExtents},
        swapChainImages{std::move(swapChainImages)},
        device{device}
    {

    }

    VulkanSwapchain::VulkanSwapchain(VulkanSwapchain &&other) noexcept :
        swapchain{other.swapchain},
        swapchainImageFormat{other.swapchainImageFormat},
        swapchainExtents{other.swapchainExtents},
        swapChainImages{std::move(other.swapChainImages)},
        device{other.device}
    {
        other.swapchain = VK_NULL_HANDLE;
        other.swapchainImageFormat = VK_FORMAT_UNDEFINED;
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
        swapchainExtents = other.swapchainExtents;
        device = other.device;
        swapChainImages = std::move(other.swapChainImages);
        other.swapchain = VK_NULL_HANDLE;
        other.swapchainImageFormat = VK_FORMAT_UNDEFINED;
        other.swapchainExtents = {0, 0};
        other.device = nullptr;
        return *this;
    }

    VulkanSwapchain::operator bool() const noexcept
    {
        return swapchain != VK_NULL_HANDLE &&
            swapchainImageFormat != VK_FORMAT_UNDEFINED &&
            swapchainExtents.width > 0 &&
            swapchainExtents.height > 0 &&
            swapChainImages.size() > 0;
    }

    VkSwapchainKHR VulkanSwapchain::getSwapchain() const noexcept
    {
        return swapchain;
    }

    VkFormat VulkanSwapchain::getImageFormat() const noexcept
    {
        return swapchainImageFormat;
    }

    VkExtent2D VulkanSwapchain::getExtents() const noexcept
    {
        return swapchainExtents;
    }

    std::vector<std::unique_ptr<IVulkanImage>> const & VulkanSwapchain::getSwapchainImages() const noexcept
    {
        return swapChainImages;
    }
}

#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanSwapchainBuilder.hpp"

namespace siofraEngine::systems
{
    VulkanSwapchain::Builder::Builder(IVulkanImageBuilder& vulkanImageBuilder) :
        vulkanImageBuilder{vulkanImageBuilder}
    {

    }

    IVulkanSwapchainBuilder& VulkanSwapchain::Builder::withDevice(IVulkanDevice const * device) noexcept
    {
        this->device = device;
        return *this;
    }

    IVulkanSwapchainBuilder& VulkanSwapchain::Builder::withSurface(IVulkanSurface const * surface) noexcept
    {
        this->surface = surface;
        return *this;
    }

    IVulkanSwapchainBuilder& VulkanSwapchain::Builder::withExtents(uint32_t width, uint32_t height) noexcept
    {
        extents.width = width;
        extents.height = height;
        return *this;
    }

    std::unique_ptr<IVulkanSwapchain> VulkanSwapchain::Builder::build() const
    {
        VkSurfaceFormatKHR surfaceFormat{ };
        selectSurfaceFormat(device, surface, surfaceFormat);

        VkPresentModeKHR presentMode{ };
		selectPresentationMode(device, surface, presentMode);

        VkExtent2D selectedExtents{ };
        uint32_t imageCount{ };
        VkSurfaceTransformFlagBitsKHR currentTransform{ };
		selectCapabilities(device, surface, extents, selectedExtents, imageCount, currentTransform);

        VkSwapchainCreateInfoKHR swapChainCreateInfo = {};
        swapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapChainCreateInfo.surface = surface->getSurface();
        swapChainCreateInfo.imageFormat = surfaceFormat.format;
        swapChainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
        swapChainCreateInfo.presentMode = presentMode;
        swapChainCreateInfo.imageExtent = selectedExtents;
        swapChainCreateInfo.minImageCount = imageCount;
        swapChainCreateInfo.imageArrayLayers = 1;
        swapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        swapChainCreateInfo.preTransform = currentTransform;
        swapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapChainCreateInfo.clipped = VK_TRUE;

        auto graphicsFamily = device->getGraphicsQueue()->getFamilyIndex();
        auto presentationFamily = device->getPresentationQueue()->getFamilyIndex();
        if (graphicsFamily != presentationFamily)
        {
            uint32_t queueFamilyIndices[] = {
                (uint32_t)graphicsFamily,
                (uint32_t)presentationFamily
            };

            swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            swapChainCreateInfo.queueFamilyIndexCount = 2;
            swapChainCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else
        {
            swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            swapChainCreateInfo.queueFamilyIndexCount = 0;
            swapChainCreateInfo.pQueueFamilyIndices = nullptr;
        }

        swapChainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

        VkSwapchainKHR swapchain{ VK_NULL_HANDLE };
        if (vkCreateSwapchainKHR(device->getLogicalDevice(), &swapChainCreateInfo, nullptr, &swapchain) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create swapchain");
        }

        uint32_t swapChainImageCount{ };
        vkGetSwapchainImagesKHR(device->getLogicalDevice(), swapchain, &swapChainImageCount, nullptr);
        std::vector<VkImage> images(swapChainImageCount);
        vkGetSwapchainImagesKHR(device->getLogicalDevice(), swapchain, &swapChainImageCount, images.data());

        std::vector<std::unique_ptr<IVulkanImage>> swapChainImages(images.size());
        for (size_t i = 0; i < swapChainImages.size(); i++)
        {
            swapChainImages[i] = vulkanImageBuilder
                .withAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT)
                .withExistingImageHandle(images[i])
                .withFormat(surfaceFormat.format)
                .withDevice(device)
                .build();
        }

        VkFormat depthFormat{};
        selectDepthFormat(
            device,
            { VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D32_SFLOAT, VK_FORMAT_D24_UNORM_S8_UINT },
            VK_IMAGE_TILING_OPTIMAL,
            VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT,
            depthFormat
        );

        std::unique_ptr<IVulkanImage> depthAttachment = vulkanImageBuilder
            .withExistingImageHandle(VK_NULL_HANDLE)
            .withDevice(device)
            .withExtents(selectedExtents.width, selectedExtents.height)
            .withFormat(depthFormat)
            .withTiling(VK_IMAGE_TILING_OPTIMAL)
            .withUsageFlags(VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
            .withMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
            .withAspectFlags(VK_IMAGE_ASPECT_DEPTH_BIT)
            .build();

        return std::make_unique<VulkanSwapchain>(swapchain, surfaceFormat.format, depthFormat, selectedExtents, std::move(swapChainImages), std::move(depthAttachment), device);
    }

    bool VulkanSwapchain::Builder::selectSurfaceFormat(IVulkanDevice const * device, IVulkanSurface const * surface, VkSurfaceFormatKHR& surfaceFormat) const
    {
        uint32_t formatCount{ 0 };
        vkGetPhysicalDeviceSurfaceFormatsKHR(device->getPhysicalDevice(), surface->getSurface(), &formatCount, nullptr);

        std::vector<VkSurfaceFormatKHR> formats(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device->getPhysicalDevice(), surface->getSurface(), &formatCount, formats.data());

        if (formats.size() == 1 && formats[0].format == VK_FORMAT_UNDEFINED)
        {
            surfaceFormat = { VK_FORMAT_R8G8B8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
        }

        for (const auto& format : formats)
        {
            if ((format.format == VK_FORMAT_R8G8B8A8_UNORM || format.format == VK_FORMAT_B8G8R8A8_UNORM) && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            {
                surfaceFormat = format;
                break;
            }
        }

        surfaceFormat = formats[0];

        return true;
    }

    bool VulkanSwapchain::Builder::selectPresentationMode(IVulkanDevice const * device, IVulkanSurface const * surface, VkPresentModeKHR& presentMode) const
    {
        uint32_t presentationCount{ 0 };
        vkGetPhysicalDeviceSurfacePresentModesKHR(device->getPhysicalDevice(), surface->getSurface(), &presentationCount, nullptr);

        std::vector<VkPresentModeKHR> presentationModes(presentationCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device->getPhysicalDevice(), surface->getSurface(), &presentationCount, presentationModes.data());

        for (const auto& presentationMode : presentationModes)
        {
            if (presentationMode == VK_PRESENT_MODE_MAILBOX_KHR)
            {
                presentMode = presentationMode;
                break;
            }
        }

        return true;
    }

    bool VulkanSwapchain::Builder::selectCapabilities(IVulkanDevice const * device, IVulkanSurface const * surface, VkExtent2D extents, VkExtent2D& outExtents, uint32_t& imageCount, VkSurfaceTransformFlagBitsKHR& currentTransform) const
    {
        VkSurfaceCapabilitiesKHR surfaceCapabilities{ };
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->getPhysicalDevice(), surface->getSurface(), &surfaceCapabilities);

        if (surfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
        {
            outExtents = surfaceCapabilities.currentExtent;
        }

        outExtents.width = std::max(surfaceCapabilities.minImageExtent.width, std::min(surfaceCapabilities.maxImageExtent.width, outExtents.width));
        outExtents.height = std::max(surfaceCapabilities.minImageExtent.height, std::min(surfaceCapabilities.maxImageExtent.height, outExtents.height));

        imageCount = surfaceCapabilities.minImageCount + 1;
        if (surfaceCapabilities.maxImageCount > 0 && surfaceCapabilities.maxImageCount < imageCount)
        {
           imageCount = surfaceCapabilities.maxImageCount;
        }

        currentTransform = surfaceCapabilities.currentTransform;

        return true;
    }

    bool VulkanSwapchain::Builder::selectDepthFormat(IVulkanDevice const * device, std::vector<VkFormat> const formats, VkImageTiling const tiling, VkFormatFeatureFlags const featureFlags, VkFormat& depthFormat) const
    {
        for (auto const & format : formats)
        {
            VkFormatProperties properties{ };
            vkGetPhysicalDeviceFormatProperties(device->getPhysicalDevice(), format, &properties);

            if (tiling == VK_IMAGE_TILING_LINEAR && (properties.linearTilingFeatures & featureFlags) == featureFlags)
            {
                depthFormat = format;
                return true;
            }
            else if (tiling == VK_IMAGE_TILING_OPTIMAL && (properties.optimalTilingFeatures & featureFlags) == featureFlags)
            {
                depthFormat = format;
                return true;
            }
        }

        return false;
    }
}

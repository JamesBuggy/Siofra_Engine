#pragma once

#include <stdexcept>
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanSwapchainBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanImageBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/vulkanSwapchain.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan swapchain builder
     */
    class VulkanSwapchain::Builder : IVulkanSwapchainBuilder
    {
    public:
        /**
         * @brief Vulkan device builder constructor
         * 
         * @param vulkanImageBuilder Vulkan image builder
         */
        Builder(IVulkanImageBuilder& vulkanImageBuilder);

        /**
         * @brief Specify the device with which to create the swapchain
         * 
         * @param device The device with which to create the swapchain
         * @returns A reference to the builder
         */
        IVulkanSwapchainBuilder& withDevice(IVulkanDevice const * device) noexcept override;

        /**
         * @brief Specify the swapchain surface
         * 
         * @param surface The swapchain surface
         * @returns A reference to the builder
         */
        IVulkanSwapchainBuilder& withSurface(IVulkanSurface const * surface) noexcept override;

        /**
         * @brief Specify the swapchain extents
         * 
         * @param width The swapchain width
         * @param height The swapchain height
         * @returns A reference to the builder
         */
        IVulkanSwapchainBuilder& withExtents(uint32_t width, uint32_t height) noexcept override;

        /**
         * @brief Build the Vulkan swapchain
         * 
         * @returns The final Vulkan swapchain
         */
        std::unique_ptr<IVulkanSwapchain> build() const override;

    private:
        /**
         * @brief Vulkan image builder
         */
        IVulkanImageBuilder& vulkanImageBuilder;

        /**
         * @brief The device with which to create the swapchain
         */
        IVulkanDevice const * device{ nullptr };

        /**
         * @brief The swapchain surface
         */
        IVulkanSurface const * surface{ nullptr };

        /**
         * @brief The swapchain extents
         */
        VkExtent2D extents{ 0, 0 };

        /**
         * @brief Select the surface format
         * 
         * @param device The vulkan device to query for format support
         * @param surface The vulkan surface to query for format support
         * @param surfaceFormat The surface format handle to populate
         * @returns True if a format was selceted, otherwise false
         */
        bool selectSurfaceFormat(IVulkanDevice const * device, IVulkanSurface const * surface, VkSurfaceFormatKHR& surfaceFormat) const;

        /**
         * @brief Select the presentation mode
         * 
         * @param device The vulkan device to query for present mode support
         * @param surface The vulkan surface to query for present mode support
         * @param presentMode The surface present mode handle to populate
         * @returns True if a present mode was selceted, otherwise false
         */
        bool selectPresentationMode(IVulkanDevice const * device, IVulkanSurface const * surface, VkPresentModeKHR& presentMode) const;

        /**
         * @brief Query the physical device and swapchain capabilities
         * 
         * @param device The vulkan device to query for extent support
         * @param surface The vulkan surface to query for extent support
         * @param extents The desired extents
         * @param outExtents The extents to populate
         * @param imageCount Supported surface transform
         * @returns True if capabilities are selceted, otherwise false
         */
        bool selectCapabilities(IVulkanDevice const * device, IVulkanSurface const * surface, VkExtent2D const extents, VkExtent2D& outExtents, uint32_t& imageCount, VkSurfaceTransformFlagBitsKHR& currentTransform) const;

        /**
         * @brief Query the physical device and swapchain capabilities
         * 
         * @param device The vulkan device to query for format support
         * @param formats List of acceptable formats
         * @param tiling Desired tiling
         * @param featureFlags Desired feature flags
         * @param depthFormat The format to populate
         * @returns True if format was selceted, otherwise false
         */
        bool selectDepthFormat(IVulkanDevice const * device, std::vector<VkFormat> const formats, VkImageTiling const tiling, VkFormatFeatureFlags const featureFlags, VkFormat& depthFormat) const;
    };
}

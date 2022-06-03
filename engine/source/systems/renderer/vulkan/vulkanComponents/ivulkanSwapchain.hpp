#pragma once

#include <vector>
#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanImage.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan swapchain interface
     */
    class IVulkanSwapchain : IVulkanComponent
    {
    public:
        /**
         * @brief Get swapchain handle
         */
        virtual VkSwapchainKHR getSwapchain() const noexcept = 0;

        /**
         * @brief Get swapchain image format
         * 
         * @returns The swapchain image format
         */
        virtual VkFormat getImageFormat() const noexcept = 0;
        
        /**
         * @brief Get the depth attchment format
         * 
         * @returns The Vulkan depth attchment format
         */
        virtual VkFormat getDepthAttachmentFormat() const noexcept = 0;

        /**
         * @brief Get swapchain extents
         */
        virtual VkExtent2D getExtents() const noexcept = 0;

        /**
         * @brief Get swapchain images
         */
        virtual std::vector<std::unique_ptr<IVulkanImage>> const & getSwapchainImages() const noexcept = 0;

        /**
         * @brief Get swapchain depth attahcment
         */
        virtual std::unique_ptr<IVulkanImage> const & getDepthAttachment() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanSwapchain() = default;
    };
}

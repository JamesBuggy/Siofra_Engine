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
         */
        virtual VkFormat getImageFormat() const noexcept = 0;

        /**
         * @brief Get swapchain extents
         */
        virtual VkExtent2D getExtents() const noexcept = 0;

        /**
         * @brief Get swapchain images
         */
        virtual std::vector<std::unique_ptr<IVulkanImage>> const & getSwapchainImages() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanSwapchain() = default;
    };
}
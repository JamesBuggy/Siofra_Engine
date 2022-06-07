#pragma once

#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanSwapchain.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanSurface.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan swapchain builder interface
     */
    class IVulkanSwapchainBuilder
    {
    public:
        /**
         * @brief Specify the device with which to create the swapchain
         * 
         * @param device The device with which to create the swapchain
         * @returns A reference to the builder
         */
        virtual IVulkanSwapchainBuilder& withDevice(IVulkanDevice const * device) noexcept = 0;

        /**
         * @brief Specify the swapchain surface
         * 
         * @param surface The swapchain surface
         * @returns A reference to the builder
         */
        virtual IVulkanSwapchainBuilder& withSurface(IVulkanSurface const * surface) noexcept = 0;

        /**
         * @brief Specify the swapchain extents
         * 
         * @param width The swapchain width
         * @param height The swapchain height
         * @returns A reference to the builder
         */
        virtual IVulkanSwapchainBuilder& withExtents(uint32_t width, uint32_t height) noexcept = 0;

        /**
         * @brief Build the Vulkan swapchain
         * 
         * @returns The final Vulkan swapchain
         */
        virtual std::unique_ptr<IVulkanSwapchain> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanSwapchainBuilder() = default;
    };
}

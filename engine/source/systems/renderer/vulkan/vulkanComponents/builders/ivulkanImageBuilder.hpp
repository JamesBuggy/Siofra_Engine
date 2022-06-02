#pragma once

#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanImage.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan image builder interface
     */
    class IVulkanImageBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the image
         * 
         * @param device The device with which to create the image
         * @returns Reference to the builder
         */
        virtual IVulkanImageBuilder& withDevice(IVulkanDevice const * device) noexcept = 0;

        /**
         * @brief Specify the image extents
         * 
         * @param width The image width
         * @param height The image height
         * @returns Reference to the builder
         */
		virtual IVulkanImageBuilder& withExtents(uint32_t width, uint32_t height) noexcept = 0;

        /**
         * @brief Specify the image format
         * 
         * @param format The image format
         * @returns Reference to the builder
         */
		virtual IVulkanImageBuilder& withFormat(VkFormat format) noexcept = 0;

        /**
         * @brief Specify the image tiling
         * 
         * @param tiling The image tiling
         * @returns Reference to the builder
         */
		virtual IVulkanImageBuilder& withTiling(VkImageTiling tiling) noexcept = 0;

        /**
         * @brief Specify the image usageFlags
         * 
         * @param usageFlags The image usageFlags
         * @returns Reference to the builder
         */
		virtual IVulkanImageBuilder& withUsageFlags(VkImageUsageFlags usageFlags) noexcept = 0;

        /**
         * @brief Specify the image memoryPropertyFlags
         * 
         * @param memoryPropertyFlags The image memoryPropertyFlags
         * @returns Reference to the builder
         */
		virtual IVulkanImageBuilder& withMemoryPropertyFlags(VkMemoryPropertyFlags memoryPropertyFlags) noexcept = 0;

        /**
         * @brief Specify the image aspectFlags
         * 
         * @param aspectFlags The image aspectFlags
         * @returns Reference to the builder
         */
		virtual IVulkanImageBuilder& withAspectFlags(VkImageAspectFlags aspectFlags) noexcept = 0;

        /**
         * @brief Specify an existing image handle for which to create a view
         * 
         * @param image The existing image handle
         * @returns Reference to the builder
         */
		virtual IVulkanImageBuilder& withExistingImageHandle(VkImage image) noexcept = 0;

        /**
         * @brief Build the Vulkan image
         * 
         * @returns The final Vulkan image
         */
        virtual std::unique_ptr<IVulkanImage> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanImageBuilder() = default;
    };
}

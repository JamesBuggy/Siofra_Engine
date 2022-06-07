#pragma once

#include <stdexcept>
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanImageBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/vulkanImage.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan image builder
     */
    class VulkanImage::Builder : public IVulkanImageBuilder
    {
    public:
        /**
         * @brief Vulkan image builder constructor
         */
        Builder() = default;

        /**
         * @brief Specify the device used to create the image
         * 
         * @param device The device with which to create the image
         * @returns Reference to the builder
         */
        IVulkanImageBuilder& withDevice(IVulkanDevice const * device) noexcept override;

        /**
         * @brief Specify the image extents
         * 
         * @param width The image width
         * @param height The image height
         * @returns Reference to the builder
         */
		IVulkanImageBuilder& withExtents(uint32_t width, uint32_t height) noexcept override;

        /**
         * @brief Specify the image format
         * 
         * @param format The image format
         * @returns Reference to the builder
         */
		IVulkanImageBuilder& withFormat(VkFormat format) noexcept override;

        /**
         * @brief Specify the image tiling
         * 
         * @param tiling The image tiling
         * @returns Reference to the builder
         */
		IVulkanImageBuilder& withTiling(VkImageTiling tiling) noexcept override;

        /**
         * @brief Specify the image usageFlags
         * 
         * @param usageFlags The image usageFlags
         * @returns Reference to the builder
         */
		IVulkanImageBuilder& withUsageFlags(VkImageUsageFlags usageFlags) noexcept override;

        /**
         * @brief Specify the image memoryPropertyFlags
         * 
         * @param memoryPropertyFlags The image memoryPropertyFlags
         * @returns Reference to the builder
         */
		IVulkanImageBuilder& withMemoryPropertyFlags(VkMemoryPropertyFlags memoryPropertyFlags) noexcept override;

        /**
         * @brief Specify the image aspectFlags
         * 
         * @param aspectFlags The image aspectFlags
         * @returns Reference to the builder
         */
		IVulkanImageBuilder& withAspectFlags(VkImageAspectFlags aspectFlags) noexcept override;

        /**
         * @brief Specify an existing image handle for which to create a view
         * 
         * @param image The existing image handle
         * @returns Reference to the builder
         */
		IVulkanImageBuilder& withExistingImageHandle(VkImage image) noexcept override;

        /**
         * @brief Build the Vulkan image
         * 
         * @returns The final Vulkan image
         */
        std::unique_ptr<IVulkanImage> build() const override;

    private:
        /**
         * @brief The device with which to create the image
         */
        IVulkanDevice const * device{ nullptr };

        /**
         * @brief The image width
         */
        uint32_t width{ };

        /**
         * @brief The image height
         */
        uint32_t height{ };

        /**
         * @brief The image format
         */
        VkFormat format{ VK_FORMAT_UNDEFINED };

        /**
         * @brief The image tiling
         */
        VkImageTiling tiling{ VK_IMAGE_TILING_OPTIMAL };

        /**
         * @brief The image usageFlags
         */
        VkImageUsageFlags usageFlags{ 0 };

        /**
         * @brief The image memoryPropertyFlags
         */
        VkMemoryPropertyFlags memoryPropertyFlags{ 0 };

        /**
         * @brief The image aspectFlags
         */
        VkImageAspectFlags aspectFlags{ VK_IMAGE_ASPECT_NONE };

        /**
         * @brief An optional existing image handle
         */
        VkImage existingImage{ VK_NULL_HANDLE };

        /**
         * @brief Create an image handle
         * 
         * @param device The device with which to create the image
         * @param width The image width
         * @param height The image height
         * @param format The image format
         * @param tiling The image tiling
         * @param usageFlags The image usageFlags
         * @param image The image handle to be populated
         * @returns True if the image handle was created, otherwise false
         */
        bool createImage(IVulkanDevice const * device, uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usageFlags, VkImage& image) const;

        /**
         * @brief Create an image view handle
         * 
         * @param device The device with which to create the image view
         * @param image The image to which the image view relates
         * @param format The image view format
         * @param aspectFlags The image view aspectFlags
         * @param imageView The image view handle to be populated
         * @returns True if the image view handle was created, otherwise false
         */
        bool createImageView(IVulkanDevice const * device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VkImageView& imageView) const;

        /**
         * @brief Allocate image memory
         * 
         * @param device The device with which to allocate the image memory
         * @param image The image for which to allocate memory
         * @param memoryPropertyFlags The image memory property flags
         * @param imageMemory The image memory handle to be populated
         * @returns True if the image memory was allocated, otherwise false
         */
        bool allocateImageMemory(IVulkanDevice const * device, VkImage image, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceMemory& imageMemory) const;

        /**
         * @brief Find the index of the required memory type, within the physical device memory properties, which satisfies the image memory requirements and the desired memory types
         * 
         * @param device The device to search for the required memory type index
         * @param allowedTypes The allowed image memory types
         * @param properties The desired memory types
         * @returns The memory type index
         */
        uint32_t findMemoryTypeIndex(IVulkanDevice const * device, uint32_t allowedTypes, VkMemoryPropertyFlags properties) const;
    };
}

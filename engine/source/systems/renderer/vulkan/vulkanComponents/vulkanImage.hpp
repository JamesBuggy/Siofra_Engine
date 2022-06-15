#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanImage.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Maintains vulkan image handle(s)
     */
    class VulkanImage : public IVulkanImage
    {
    public:
        /**
         * @brief VulkanImage builder
         */
        class Builder;

        /**
         * @brief VulkanImage constructor
         * 
         * @param image Vulkan image handle
         * @param imageView Vulkan image view handle
         * @param imageMemory Vulkan image memory handle
         * @param managedImage Indicate if the image and image memory handles are managed elsewhere
         * @param device The device used to create the image
         */
        VulkanImage(VkImage image, VkImageView imageView, VkDeviceMemory imageMemory, bool managedImage, IVulkanDevice const * device);

        /**
         * @brief VulkanImage copy constructor
         * 
         * @param other VulkanImage to copy
         */
        VulkanImage(VulkanImage const &other) = delete;

        /**
         * @brief VulkanImage move constructor
         * 
         * @param other VulkanImage to move
         */
        VulkanImage(VulkanImage &&other) noexcept;

        /**
         * @brief VulkanImage destructor
         */
        ~VulkanImage();

        /**
         * @brief VulkanImage copy assignment
         * 
         * @param other VulkanImage to copy
         */
        VulkanImage& operator=(const VulkanImage &other) = delete;

        /**
         * @brief VulkanImage move assignment
         * 
         * @param other VulkanImage to move
         */
        VulkanImage& operator=(VulkanImage &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;

        /**
         * @brief Get the image view handle
         * 
         * @returns The image view handle
         */
        VkImageView getImageView() const noexcept override;

        /**
         * @brief Get the image handle
         * 
         * @returns The image handle
         */
        VkImage getImage() const noexcept override;

        /**
         * @brief Transition the image layout
         * 
         * @param commandBuffer The command buffer to record on
         * @param queue The queue on which to submit the command buffer
         * @param oldLayout The old image layout
         * @param newLayout The new image layout
         */
        void transitionImageLayout(IVulkanCommandBuffer const * commandBuffer, IVulkanQueue const * queue, VkImageLayout oldLayout, VkImageLayout newLayout) const override;
        
    private:
        /**
         * @brief Vulkan image handle
         */
        VkImage image{ VK_NULL_HANDLE };

        /**
         * @brief Vulkan image view handle
         */
        VkImageView imageView{ VK_NULL_HANDLE };

        /**
         * @brief Vulkan image memory handle
         */
        VkDeviceMemory imageMemory{ VK_NULL_HANDLE };

        /**
         * @brief Indicates if the image and image memory handles are managed elsewhere
         */
        bool managedImage{ false };

        /**
         * @brief The device used to create the image
         */
        IVulkanDevice const * device{ nullptr };
    };
}

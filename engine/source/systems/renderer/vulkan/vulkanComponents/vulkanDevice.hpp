#pragma once

#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanQueue.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Maintains vulkan device handles
     */
    class VulkanDevice : public IVulkanDevice
    {
    public:
        /**
         * @brief VulkanDevice builder
         */
        class Builder;

        /**
         * @brief VulkanDevice constructor
         * 
         * @param physicalDevice Vulkan physical device handle
         * @param logicalDevice Vulkan logical device handle
         * @param graphicsQueue Graphics queue handle
         * @param presentationQueue presentation queue handle
         * @param transferQueue Transfer queue handle
         * @param computeQueue Compute queue handle
         */
        VulkanDevice(
            VkPhysicalDevice physicalDevice,
            VkDevice logicalDevice,
            std::unique_ptr<IVulkanQueue> graphicsQueue,
            std::unique_ptr<IVulkanQueue> presentationQueue,
            std::unique_ptr<IVulkanQueue> transferQueue,
            std::unique_ptr<IVulkanQueue> computeQueue);

        /**
         * @brief VulkanDevice copy constructor
         * 
         * @param other VulkanDevice to copy
         */
        VulkanDevice(VulkanDevice const &other) = delete;

        /**
         * @brief VulkanDevice move constructor
         * 
         * @param other VulkanDevice to move
         */
        VulkanDevice(VulkanDevice &&other) noexcept;

        /**
         * @brief VulkanDevice destructor
         */
        ~VulkanDevice();

        /**
         * @brief VulkanDevice copy assignment
         * 
         * @param other VulkanDevice to copy
         */
        VulkanDevice& operator=(const VulkanDevice &other) = delete;

        /**
         * @brief VulkanDevice move assignment
         * 
         * @param other VulkanDevice to move
         */
        VulkanDevice& operator=(VulkanDevice &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;

    private:
        /**
         * @brief Vulkan physical device handle
         */
        VkPhysicalDevice physicalDevice{ VK_NULL_HANDLE };

        /**
         * @brief Vulkan logical device handle
         */
        VkDevice logicalDevice{ VK_NULL_HANDLE };

        /**
         * @brief Graphics queue handle
         */
        std::unique_ptr<IVulkanQueue> graphicsQueue{ nullptr };

        /**
         * @brief Presentation queue handle
         */
        std::unique_ptr<IVulkanQueue> presentationQueue{ nullptr };

        /**
         * @brief Transfer queue handle
         */
        std::unique_ptr<IVulkanQueue> transferQueue{ nullptr };

        /**
         * @brief Compute queue handle
         */
        std::unique_ptr<IVulkanQueue> computeQueue{ nullptr };
    };
}

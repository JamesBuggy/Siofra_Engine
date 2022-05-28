#pragma once

#include <stdexcept>
#include <set>
#include "core/logging.hpp"
#include "systems/renderer/vulkan/vulkanComponents/vulkanDevice.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanDeviceBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanQueueBuilder.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan device builder
     */
    class VulkanDevice::Builder : public IVulkanDeviceBuilder
    {
    public:
        /**
         * @brief Vulkan device builder constructor
         * 
         * @param vulkanQueueBuilder Vulkan queue builder
         */
        Builder(IVulkanQueueBuilder& vulkanQueueBuilder);
        
        /**
         * @brief Specify minimum required Vulkan API version
         * 
         * @param major Vulkan API major version
         * @param minor Vulkan API minor version
         * @returns Reference to the builder
         */
        IVulkanDeviceBuilder& withApiVersionSupport(uint32_t major, uint32_t minor) noexcept override;

        /**
         * @brief Specify required queue families
         * 
         * @param requiredQueueFamilies Required queue families
         * @returns Reference to the builder
         */
        IVulkanDeviceBuilder& withQueueFamilySupport(VulkanDeviceQueueFamilies requiredQueueFamilies) noexcept override;

        /**
         * @brief Specify required extensions
         * 
         * @param requiredExtensions Required extensions
         * @returns Reference to the builder
         */
        IVulkanDeviceBuilder& withExtensionSupport(std::vector<const char*> requiredExtensions) noexcept override;

        /**
         * @brief Specify the vulkan surface to be used for presentation to ensure support
         * 
         * @param surface The vulkan surface used for presentation
         * @returns Reference to the builder
         */
        IVulkanDeviceBuilder& withSurfacePresentationSupport(IVulkanSurface const *surface) noexcept override;

        /**
         * @brief Specify the vulkan instance
         * 
         * @param instance The vulkan instance
         * @returns Reference to the builder
         */
        IVulkanDeviceBuilder& withInstance(IVulkanInstance const *instance) noexcept override;

        /**
         * @brief Specify the validation layers to enable
         * 
         * @param validationLayers The validation layers to enable
         * @returns Reference to the builder
         */
        IVulkanDeviceBuilder& withValidationLayers(std::vector<const char*> validationLayers) noexcept override;

        /**
         * @brief Build the Vulkan device
         * 
         * @returns The final Vulkan device
         */
        std::unique_ptr<IVulkanDevice> build() const override;
        
    private:
        /**
         * @brief Vulkan queue builder
         */
        IVulkanQueueBuilder& vulkanQueueBuilder;

        /**
         * @brief Minimum Vulkan API major version number
         */
        uint32_t apiMinimumMajorVersion{ 1 };

        /**
         * @brief Minimum Vulkan API minor version number
         */
        uint32_t apiMinimumMinorVersion{ 0 };

        /**
         * @brief Required queue families
         */
        VulkanDeviceQueueFamilies requiredQueueFamilies{ VulkanDeviceQueueFamilies::GRAPHICS | VulkanDeviceQueueFamilies::PRESENTATION };

        /**
         * @brief Required extensions to support
         */
        std::vector<const char*> requiredDeviceExtensions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };

        /**
         * @brief The vulkan surface used for presentation
         */
        IVulkanSurface const *surface{ nullptr };

        /**
         * @brief The vulkan instance
         */
        IVulkanInstance const *instance{ nullptr };

        /**
         * @brief Device validation layers
         */
        std::vector<const char*> validationLayers{ };

        /**
         * @brief Device queue family indicies
         */
        struct QueueFamilyIndicies {
            int32_t graphics = -1;
            int32_t presentation = -1;
            int32_t transfer = -1;
            int32_t compute = -1;

            bool areValid(VulkanDeviceQueueFamilies const requiredQueueFamilies) const
            {
                if((graphics == -1 && (requiredQueueFamilies & VulkanDeviceQueueFamilies::GRAPHICS) == VulkanDeviceQueueFamilies::GRAPHICS) ||
                    (presentation == -1 && (requiredQueueFamilies & VulkanDeviceQueueFamilies::PRESENTATION) == VulkanDeviceQueueFamilies::PRESENTATION) ||
                    (transfer == -1 && (requiredQueueFamilies & VulkanDeviceQueueFamilies::TRANSFER) == VulkanDeviceQueueFamilies::TRANSFER) ||
                    (compute == -1 && (requiredQueueFamilies & VulkanDeviceQueueFamilies::COMPUTE) == VulkanDeviceQueueFamilies::COMPUTE))
                {
                    return false;
                }
                return true;
            }
        };

        /**
         * @brief Choose a physical device
         * 
         * @param instance The vulkan instance
         * @param surface The presentation surface
         * @param requiredQueueFamilies Required queue families
         * @param requiredDeviceExtensions Required extensions to support
         * @returns A handle to the chosen physical device
         */
        VkPhysicalDevice findPhysicalDevice(IVulkanInstance const *instance, IVulkanSurface const *surface, VulkanDeviceQueueFamilies const requiredQueueFamilies, std::vector<const char*> const requiredDeviceExtensions) const;

        /**
         * @brief Create a logical device
         * 
         * @param physicalDevice The related physical device
         * @param validationLayers Validation layers to enable
         * @param requiredDeviceExtensions Required device extensions
         * @param queueFamilyIdicies Queue family indicies
         * @returns A handle to the create logical device
         */
        VkDevice createLogicalDevice(VkPhysicalDevice const physicalDevice, std::vector<const char*> const validationLayers, std::vector<const char*> requiredDeviceExtensions, QueueFamilyIndicies const queueFamilyIdicies) const;

        /**
         * @brief Find a physical devices queue family indicies
         * 
         * @param physicalDevice The physical device
         * @param surface The presentation surface
         * @param requiredQueueFamilies Required queue families
         * @returns The queue family indicies
         */
        QueueFamilyIndicies findDeviceQueueFamilyIndicies(VkPhysicalDevice const physicalDevice, IVulkanSurface const *surface) const;

        /**
         * @brief Check if a physical device supports the required extensions
         * 
         * @param physicalDevice The physical device
         * @param requiredDeviceExtensions Required extensions to support
         * @returns Whether or not the required extensions are supported
         */
        bool checkPhysicalDeviceExtensionSupport(VkPhysicalDevice const physicalDevice, std::vector<const char*> const requiredDeviceExtensions) const;

        /**
         * @brief Check if a physical device has swapchain support
         * 
         * @param physicalDevice The physical device
         * @param surface The surface that will be associated with the swapchain
         * @returns Whether or not the physical device has swapchain support
         */
        bool checkPhysicalDeviceSwapchainSupport(VkPhysicalDevice const physicalDevice, IVulkanSurface const *surface) const;
    };
}

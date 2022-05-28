#pragma once

#include <memory>
#include <vector>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanSurface.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanInstance.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Flags to specify Vulkan queue families
     */
    enum class VulkanDeviceQueueFamilies
    {
        GRAPHICS = 1 << 0,
        PRESENTATION = 1 << 1,
        TRANSFER = 1 << 2,
        COMPUTE = 1 << 3
    };

    inline VulkanDeviceQueueFamilies operator|(VulkanDeviceQueueFamilies a, VulkanDeviceQueueFamilies b)
    {
        return static_cast<VulkanDeviceQueueFamilies>(static_cast<int>(a) | static_cast<int>(b));
    }

    inline VulkanDeviceQueueFamilies operator&(VulkanDeviceQueueFamilies a, VulkanDeviceQueueFamilies b)
    {
        return static_cast<VulkanDeviceQueueFamilies>(static_cast<int>(a) & static_cast<int>(b));
    }

    /**
     * @brief Vulkan device builder interface
     */
    class IVulkanDeviceBuilder
    {
    public:
        /**
         * @brief Specify minimum required Vulkan API version
         * 
         * @param major Vulkan API major version
         * @param minor Vulkan API minor version
         * @returns Reference to the builder
         */
        virtual IVulkanDeviceBuilder& withApiVersionSupport(uint32_t major, uint32_t minor) noexcept = 0;

        /**
         * @brief Specify required queue families
         * 
         * @param requiredQueueFamilies Required queue families
         * @returns Reference to the builder
         */
        virtual IVulkanDeviceBuilder& withQueueFamilySupport(VulkanDeviceQueueFamilies requiredQueueFamilies) noexcept = 0;

        /**
         * @brief Specify required extensions
         * 
         * @param requiredExtensions Required extensions
         * @returns Reference to the builder
         */
        virtual IVulkanDeviceBuilder& withExtensionSupport(std::vector<const char*> requiredExtensions) noexcept = 0;

        /**
         * @brief Specify the vulkan surface to be used for presentation to ensure support
         * 
         * @param surface The vulkan surface used for presentation
         * @returns Reference to the builder
         */
        virtual IVulkanDeviceBuilder& withSurfacePresentationSupport(IVulkanSurface const *surface) noexcept = 0;

        /**
         * @brief Specify the vulkan instance
         * 
         * @param instance The vulkan instance
         * @returns Reference to the builder
         */
        virtual IVulkanDeviceBuilder& withInstance(IVulkanInstance const *instance) noexcept = 0;

        /**
         * @brief Specify the validation layers to enable
         * 
         * @param validationLayers The validation layers to enable
         * @returns Reference to the builder
         */
        virtual IVulkanDeviceBuilder& withValidationLayers(std::vector<const char*> validationLayers) noexcept = 0;

        /**
         * @brief Build the Vulkan device
         * 
         * @returns The final Vulkan device
         */
        virtual std::unique_ptr<IVulkanDevice> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanDeviceBuilder() = default;
    };
}

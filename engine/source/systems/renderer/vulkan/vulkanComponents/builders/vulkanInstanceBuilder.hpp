#pragma once

#include <stdexcept>
#include <vector>
#include "systems/renderer/vulkan/vulkanComponents/vulkanInstance.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief VulkanInstance builder
     */
    class VulkanInstance::Builder
    {
    public:
        /**
         * @brief VulkanInstance builder constructor
         */
        Builder() = default;

        /**
         * @brief Set Vulkan API version
         * 
         * @returns Reference to the VulkanInstance builder
         */
        VulkanInstance::Builder& withApiVersion(uint32_t major, uint32_t minor) noexcept;

        /**
         * @brief Set engine version
         * 
         * @returns Reference to the VulkanInstance builder
         */
        VulkanInstance::Builder& withEngineVersion(uint32_t major, uint32_t minor) noexcept;

        /**
         * @brief Set application version
         * 
         * @returns Reference to the VulkanInstance builder
         */
        VulkanInstance::Builder& withApplicationVersion(uint32_t major, uint32_t minor) noexcept;

        /**
         * @brief Add instance extensions to the VulkanInstance
         * 
         * @returns Reference to the VulkanInstance builder
         */
        VulkanInstance::Builder& withInstanceExtensions(std::vector<const char*> instanceExtensions) noexcept;

        /**
         * @brief Enable validation layers and debug callback
         * 
         * @returns Reference to the VulkanInstance builder
         */
        VulkanInstance::Builder& withDebugUtilities() noexcept;

        /**
         * @brief Build the VulkanInstance
         * 
         * @returns The final VulkanInstance
         */
        VulkanInstance build() const;

    private:
        /**
         * @brief Vulkan API major version number
         */
        uint32_t apiMajorVersion{ 1 };

        /**
         * @brief Vulkan API minor version number
         */
        uint32_t apiMinorVersion{ 0 };

        /**
         * @brief Engine major version number
         */
        uint32_t engineMajorVersion{ 1 };

        /**
         * @brief Engine minor version number
         */
        uint32_t engineMinorVersion{ 0 };

        /**
         * @brief Application major version number
         */
        uint32_t applicationMajorVersion{ 1 };

        /**
         * @brief Application minor version number
         */
        uint32_t applicationMinorVersion{ 0 };

        /**
         * @brief Whether or not to enable validation layers and debug callback
         */
        bool enableDebugUtilities{ false };

        /**
         * @brief Extensions to include in the Vulkan instance
         */
        std::vector<const char*> instanceExtensions{ };

        /**
         * @brief Instance validation layers
         */
        std::vector<const char*> validationLayers{ "VK_LAYER_KHRONOS_validation" };

        /**
         * @brief Instance debug extensions
         */
        std::vector<const char*> debugExtensions = { VK_EXT_DEBUG_UTILS_EXTENSION_NAME };

        /**
         * @brief Debug create info
         */
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{ };

        /**
         * @brief Check support for specified instance extensions
         * 
         * @param checkExtensions Instance extensions to check
         * @returns True if specified extensions are supported, otherwise false
         */
        bool checkInstanceExtensionSupport(std::vector<const char*> const &checkExtensions) const noexcept;

        /**
         * @brief Create a persistent debug messenger
         * 
         * @param instance Vulkan instance to create debug messenger on
         * @param createInfo Debug messenger create info
         * @param allocator Custom memory allocator
         * @param debugMessenger Debug messenger handle to be populated
         * @returns True if specified extensions are supported, otherwise false
         */
        VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger) const noexcept;
    };
}
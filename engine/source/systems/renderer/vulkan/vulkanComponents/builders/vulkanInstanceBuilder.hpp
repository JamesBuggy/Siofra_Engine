#pragma once

#include <stdexcept>
#include "systems/renderer/vulkan/vulkanComponents/vulkanInstance.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanInstanceBuilder.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan instance builder
     */
    class VulkanInstance::Builder : public IVulkanInstanceBuilder
    {
    public:
        /**
         * @brief Vulkan instance builder constructor
         */
        Builder() = default;

        /**
         * @brief Set Vulkan API version
         * 
         * @param major Vulkan API major version
         * @param minor Vulkan API minor version
         * @returns Reference to the builder
         */
        IVulkanInstanceBuilder& withApiVersion(uint32_t major, uint32_t minor) noexcept override;

        /**
         * @brief Set engine version
         * 
         * @param major Engine major version
         * @param minor Engine minor version
         * @returns Reference to the builder
         */
        IVulkanInstanceBuilder& withEngineVersion(uint32_t major, uint32_t minor) noexcept override;

        /**
         * @brief Set application version
         * 
         * @param major Application major version
         * @param minor Application minor version
         * @returns Reference to the builder
         */
        IVulkanInstanceBuilder& withApplicationVersion(uint32_t major, uint32_t minor) noexcept override;

        /**
         * @brief Add instance extensions to the Vulkan instance
         * 
         * @param instanceExtensions Instance extensions
         * @returns Reference to the builder
         */
        IVulkanInstanceBuilder& withInstanceExtensions(std::vector<const char*> instanceExtensions) noexcept override;

        /**
         * @brief Specify the validation layers to enable
         * 
         * @param validationLayers The validation layers to enable
         * @returns Reference to the builder
         */
        IVulkanInstanceBuilder& withValidationLayers(std::vector<const char*> validationLayers) noexcept override;

        /**
         * @brief Enable validation layers and debug callback
         * 
         * @returns Reference to the builder
         */
        IVulkanInstanceBuilder& withDebugUtilities() noexcept override;

        /**
         * @brief Build the Vulkan instance
         * 
         * @returns The final Vulkan instance
         */
        std::unique_ptr<IVulkanInstance> build() const override;

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
        std::vector<const char*> validationLayers{ };

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

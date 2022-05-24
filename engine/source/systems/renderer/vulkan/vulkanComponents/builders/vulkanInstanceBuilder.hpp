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
         * @brief Build the VulkanInstance
         * 
         * @returns The final VulkanInstance
         */
        VulkanInstance build() const;

    private:
        /**
         * @brief Extensions to include in the Vulkan instance
         */
        std::vector<const char*> instanceExtensions{ };

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
         * @brief Check support for specified instance extensions
         * 
         * @param checkExtensions Instance extensions to check
         * @returns True if specified extensions are supported, otherwise false
         */
        bool checkInstanceExtensionSupport(std::vector<const char*> const &checkExtensions) const noexcept;
    };
}
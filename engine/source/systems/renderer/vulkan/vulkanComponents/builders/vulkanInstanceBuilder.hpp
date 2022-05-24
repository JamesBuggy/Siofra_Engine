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
        Builder();

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
        std::vector<const char*> instanceExtensions;

        /**
         * @brief Check support for specified instance extensions
         * 
         * @param checkExtensions Instance extensions to check
         * @returns True if specified extensions are supported, otherwise false
         */
        bool checkInstanceExtensionSupport(std::vector<const char*> const &checkExtensions) const noexcept;
    };
}
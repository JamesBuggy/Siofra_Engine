#pragma once

#include <memory>
#include <vector>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanInstance.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan instance builder interface
     */
    class IVulkanInstanceBuilder
    {
    public:
        /**
         * @brief Set Vulkan API version
         * 
         * @param major Vulkan API major version
         * @param minor Vulkan API minor version
         * @returns Reference to the builder
         */
        virtual IVulkanInstanceBuilder& withApiVersion(uint32_t major, uint32_t minor) noexcept = 0;

        /**
         * @brief Set engine version
         * 
         * @param major Engine major version
         * @param minor Engine minor version
         * @returns Reference to the builder
         */
        virtual IVulkanInstanceBuilder& withEngineVersion(uint32_t major, uint32_t minor) noexcept = 0;

        /**
         * @brief Set application version
         * 
         * @param major Application major version
         * @param minor Application minor version
         * @returns Reference to the builder
         */
        virtual IVulkanInstanceBuilder& withApplicationVersion(uint32_t major, uint32_t minor) noexcept = 0;

        /**
         * @brief Add instance extensions to the Vulkan instance
         * 
         * @param instanceExtensions Instance extensions
         * @returns Reference to the builder
         */
        virtual IVulkanInstanceBuilder& withInstanceExtensions(std::vector<const char*> instanceExtensions) noexcept = 0;

        /**
         * @brief Specify the validation layers to enable
         * 
         * @param validationLayers The validation layers to enable
         * @returns Reference to the builder
         */
        virtual IVulkanInstanceBuilder& withValidationLayers(std::vector<const char*> validationLayers) noexcept = 0;

        /**
         * @brief Enable validation layers and debug callback
         * 
         * @returns Reference to the builder
         */
        virtual IVulkanInstanceBuilder& withDebugUtilities() noexcept = 0;

        /**
         * @brief Build the Vulkan instance
         * 
         * @returns The final Vulkan instance
         */
        virtual std::unique_ptr<IVulkanInstance> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanInstanceBuilder() = default;
    };
}

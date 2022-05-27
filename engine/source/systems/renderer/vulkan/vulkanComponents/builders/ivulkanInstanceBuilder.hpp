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
         * @returns Reference to the builder
         */
        virtual IVulkanInstanceBuilder& withApiVersion(uint32_t major, uint32_t minor) noexcept = 0;

        /**
         * @brief Set engine version
         * 
         * @returns Reference to the builder
         */
        virtual IVulkanInstanceBuilder& withEngineVersion(uint32_t major, uint32_t minor) noexcept = 0;

        /**
         * @brief Set application version
         * 
         * @returns Reference to the builder
         */
        virtual IVulkanInstanceBuilder& withApplicationVersion(uint32_t major, uint32_t minor) noexcept = 0;

        /**
         * @brief Add instance extensions to the Vulkan instance
         * 
         * @returns Reference to the builder
         */
        virtual IVulkanInstanceBuilder& withInstanceExtensions(std::vector<const char*> instanceExtensions) noexcept = 0;

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

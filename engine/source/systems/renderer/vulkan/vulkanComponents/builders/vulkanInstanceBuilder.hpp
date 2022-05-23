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
         */
        VulkanInstance::Builder& withInstanceExtensions(std::vector<const char*> instanceExtensions);

        /**
         * @brief Build the VulkanInstance
         */
        VulkanInstance build();

    private:
        /**
         * @brief Extensions to include in the Vulkan instance
         */
        std::vector<const char*> instanceExtensions;

        /**
         * @brief Check support for specified instance extensions
         */
        bool checkInstanceExtensionSupport(std::vector<const char*>* checkExtensions);
    };
}
#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan descriptor set layout interface
     */
    class IVulkanDescriptorSetLayout : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the Vulkan descriptor set layout handle
         * 
         * @returns The Vulkan descriptor set layout handle
         */
        virtual VkDescriptorSetLayout getDescriptorSetLayout() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanDescriptorSetLayout() = default;
    };
}

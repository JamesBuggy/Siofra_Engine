#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan descriptor set interface
     */
    class IVulkanDescriptorSet : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the Vulkan descriptor set handle
         * 
         * @returns The Vulkan descriptor set handle
         */
        virtual VkDescriptorSet getDescriptorSet() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanDescriptorSet() = default;
    };
}

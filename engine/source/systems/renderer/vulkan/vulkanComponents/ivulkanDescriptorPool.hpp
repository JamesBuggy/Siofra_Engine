#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan descriptor pool interface
     */
    class IVulkanDescriptorPool : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the Vulkan descriptor pool handle
         * 
         * @returns The Vulkan descriptor pool handle
         */
        virtual VkDescriptorPool getDescriptorPool() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanDescriptorPool() = default;
    };
}

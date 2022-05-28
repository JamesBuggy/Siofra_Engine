#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan device interface
     */
    class IVulkanDevice : public IVulkanComponent
    {
    public:

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanDevice() = default;
    };
}

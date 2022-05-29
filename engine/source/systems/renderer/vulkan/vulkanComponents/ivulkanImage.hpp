#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan image interface
     */
    class IVulkanImage : public IVulkanComponent
    {
    public:
        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanImage() = default;
    };
}

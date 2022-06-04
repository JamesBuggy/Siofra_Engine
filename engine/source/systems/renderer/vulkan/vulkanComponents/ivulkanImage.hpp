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
         * @brief Get the image view handle
         * 
         * @returns The image view handle
         */
        virtual VkImageView getImageView() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanImage() = default;
    };
}

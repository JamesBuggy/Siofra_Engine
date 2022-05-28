#pragma once

#include <vulkan/vulkan.h>

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan component interface
     */
    class IVulkanComponent
    {
    public:
        /**
         * @brief Check if the wrapped handle(s) are initialized
         * 
         * @returns True if the wrapped handle(s) are intialized, otherwise false
         */
        virtual operator bool() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanComponent() = default;
    };
}

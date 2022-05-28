#pragma once

#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanSurface.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanInstance.hpp"
#include "platform/iwindow.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan surface builder interface
     */
    class IVulkanSurfaceBuilder
    {
    public:
        /**
         * @brief Specify the vulkan instance that the Vulkan surface should relate to
         * 
         * @param instance The vulkan instance that the Vulkan surface should relate to
         * @returns Reference to the Vulkan surface builder
         */
        virtual IVulkanSurfaceBuilder& withInstance(IVulkanInstance const *instance) noexcept = 0;
        
        /**
         * @brief Specify the window that the Vulkan surface should relate to
         * 
         * @param window The window that the Vulkan surface should relate to
         * @returns Reference to the Vulkan surface builder
         */
        virtual IVulkanSurfaceBuilder& withWindow(siofraEngine::platform::IWindow const *window) noexcept = 0;

        /**
         * @brief Build the Vulkan surface
         * 
         * @returns The final Vulkan surface
         */
        virtual std::unique_ptr<IVulkanSurface> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanSurfaceBuilder() = default;
    };
}

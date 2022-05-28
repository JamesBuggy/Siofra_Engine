#pragma once

#include "systems/renderer/vulkan/vulkanComponents/vulkanSurface.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanSurfaceBuilder.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan surface builder
     */
    class VulkanSurface::Builder : public IVulkanSurfaceBuilder
    {
    public:
        /**
         * @brief Vulkan surface builder constructor
         */
        Builder() = default;

        /**
         * @brief Specify the vulkan instance that the Vulkan surface should relate to
         * 
         * @param instance The vulkan instance that the Vulkan surface should relate to
         * @returns Reference to the Vulkan surface builder
         */
        IVulkanSurfaceBuilder& withInstance(IVulkanInstance const *instance) noexcept override;
        
        /**
         * @brief Specify the window that the Vulkan surface should relate to
         * 
         * @param window The window that the Vulkan surface should relate to
         * @returns Reference to the Vulkan surface builder
         */
        IVulkanSurfaceBuilder& withWindow(siofraEngine::platform::IWindow const *window) noexcept override;

        /**
         * @brief Build the Vulkan surface
         * 
         * @returns The final Vulkan surface
         */
        std::unique_ptr<IVulkanSurface> build() const override;

    private:
        /**
         * @brief The vulkan instance that the Vulkan surface should relate to
         */
        IVulkanInstance const *instance{ nullptr };

        /**
         * @brief The window that the Vulkan surface should relate to
         */
        siofraEngine::platform::IWindow const *window{ nullptr };
    };
}

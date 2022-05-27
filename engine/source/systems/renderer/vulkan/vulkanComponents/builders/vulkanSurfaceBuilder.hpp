#include "systems/renderer/vulkan/vulkanComponents/vulkanSurface.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanInstance.hpp"
#include "platform/iwindow.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief VulkanSurface builder
     */
    class VulkanSurface::Builder
    {
    public:
        /**
         * @brief VulkanSurface builder constructor
         */
        Builder() = default;

        /**
         * @brief Specify the vulkan instance that the VulkanSurface should relate to
         * 
         * @returns Reference to the VulkanSurface builder
         */
        VulkanSurface::Builder& withInstance(siofraEngine::systems::IVulkanInstance const *instance) noexcept;
        
        /**
         * @brief Specify the window that the VulkanSurface should relate to
         * 
         * @returns Reference to the VulkanSurface builder
         */
        VulkanSurface::Builder& withWindow(siofraEngine::platform::IWindow const *window) noexcept;

        /**
         * @brief Build the VulkanSurface
         * 
         * @returns The final VulkanSurface
         */
        VulkanSurface build() const;

    private:
        /**
         * @brief The vulkan instance that the VulkanSurface should relate to
         */
        siofraEngine::systems::IVulkanInstance const *instance{ nullptr };

        /**
         * @brief The window that the VulkanSurface should relate to
         */
        siofraEngine::platform::IWindow const *window{ nullptr };
    };
}

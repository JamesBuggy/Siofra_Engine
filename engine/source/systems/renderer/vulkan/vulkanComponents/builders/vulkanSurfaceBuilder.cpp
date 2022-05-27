#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanSurfaceBuilder.hpp"

namespace siofraEngine::systems
{
    VulkanSurface::Builder& VulkanSurface::Builder::withInstance(siofraEngine::systems::IVulkanInstance const *instance) noexcept
    {
        this->instance = instance;
        return *this;
    }

    VulkanSurface::Builder& VulkanSurface::Builder::withWindow(siofraEngine::platform::IWindow const *window) noexcept
    {
        this->window = window;
        return *this;
    }

    VulkanSurface VulkanSurface::Builder::build() const
    {
        VkSurfaceKHR surface = VK_NULL_HANDLE;
        if (!window->createVulkanWindowSurface(instance->getInstance(), surface))
        {
            throw std::runtime_error("Failed to create window surface");
        }

        return VulkanSurface(surface, instance);
    }
}

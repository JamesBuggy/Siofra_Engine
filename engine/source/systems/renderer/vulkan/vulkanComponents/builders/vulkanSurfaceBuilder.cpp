#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanSurfaceBuilder.hpp"

namespace siofraEngine::systems
{
    IVulkanSurfaceBuilder& VulkanSurface::Builder::withInstance(IVulkanInstance const *instance) noexcept
    {
        this->instance = instance;
        return *this;
    }

    IVulkanSurfaceBuilder& VulkanSurface::Builder::withWindow(siofraEngine::platform::IWindow const *window) noexcept
    {
        this->window = window;
        return *this;
    }

    std::unique_ptr<IVulkanSurface> VulkanSurface::Builder::build() const
    {
        VkSurfaceKHR surface = VK_NULL_HANDLE;
        if (!window->createVulkanWindowSurface(instance->getInstance(), surface))
        {
            throw std::runtime_error("Failed to create window surface");
        }

        return std::make_unique<VulkanSurface>(surface, instance);
    }
}

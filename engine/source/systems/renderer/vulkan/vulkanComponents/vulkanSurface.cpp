#include "systems/renderer/vulkan/vulkanComponents/vulkanSurface.hpp"

namespace siofraEngine::systems
{
    VulkanSurface::VulkanSurface(VkSurfaceKHR surface, IVulkanInstance const *instance) :
        surface{surface},
        instance{instance}
    {
        
    }

    VulkanSurface::VulkanSurface(VulkanSurface &&other) noexcept:
        surface{other.surface},
        instance{other.instance}
    {
        other.surface = VK_NULL_HANDLE;
    }

    VulkanSurface::~VulkanSurface()
    {
        vkDestroySurfaceKHR(instance->getInstance(), surface, nullptr);
    }

    VulkanSurface& VulkanSurface::operator=(VulkanSurface &&other) noexcept
    {
        surface = other.surface;
        instance = other.instance;
        other.surface = VK_NULL_HANDLE;
        other.instance = nullptr;
        return *this;
    }

    VulkanSurface::operator bool() const noexcept
    {
        return surface != VK_NULL_HANDLE;
    }

    VkSurfaceKHR VulkanSurface::getSurface() const noexcept
    {
        return surface;
    }
}

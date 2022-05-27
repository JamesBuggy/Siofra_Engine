#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace siofraEngine::platform
{
    /**
     * @brief Flgas to specify window properties
     */
    enum class WindowFlags
    {
        WINDOW_VULKAN = 1 << 0
    };

    inline WindowFlags operator|(WindowFlags a, WindowFlags b)
    {
        return static_cast<WindowFlags>(static_cast<int>(a) | static_cast<int>(b));
    }

    inline WindowFlags operator&(WindowFlags a, WindowFlags b)
    {
        return static_cast<WindowFlags>(static_cast<int>(a) & static_cast<int>(b));
    }

    /**
     * @brief Window interface
     */
    class IWindow
    {
    public:
        /**
         * @brief Get flags applied to the window
         * 
         * @returns Flags applied to the window
         */
        virtual WindowFlags getFlags() const = 0;

        /**
         * @brief Get the names of the Vulkan instance extensions needed to create a surface
         * 
         * @returns Required instance extension names
         */
        virtual std::vector<const char*> getRequiredVulkanInstanceExtensions() const = 0;

        /**
         * @brief Creates a vulkan surface for the given vulkan instance
         * 
         * @param instance Vulkan instance to relate the surface to
         * @param surface Vulkan surface handle to be populated
         * @returns Result of the surface creation
         */
        virtual bool createVulkanWindowSurface(VkInstance const instance, VkSurfaceKHR &surface) const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IWindow() = default;
    };
}

#pragma once

#include <string>
#include <memory>
#include <cstdint>
#include "platform/iwindow.hpp"
#include "core/assertions.hpp"

namespace siofraEngine::platform
{
    /**
     * @brief Wraps plaftorm specific window logic
     */
    class Window : public IWindow
    {
    public:
        /**
         * @brief Window Constructor
         * 
         * @param title Window title
         * @param x Initial window X coordinate
         * @param y Initial window Y coordinate
         * @param width Initial window width
         * @param height Initial window height
         */
        Window(std::string title, std::uint32_t x, std::uint32_t y, std::uint32_t width, std::uint32_t height, WindowFlags flags);

        /**
         * @brief Window destructor
         */
        ~Window();

        /**
         * @brief Get flags applied to the window
         * 
         * @returns Flags applied to the window
         */
        WindowFlags getFlags() override;

        /**
         * @brief Get the names of the Vulkan instance extensions needed to create a surface
         * 
         * @returns Required instance extension names
         */
        std::vector<const char*> getRequiredVulkanInstanceExtensions() override;

    private:

        /**
         * @brief Wraps plaftorm specific window state
         */
        class InternalWindow;

        /**
         * @brief Plaftorm specific window state
         */
        std::unique_ptr<InternalWindow> _internalWindow;

        /**
         * @brief Flags applied to the window
         */
        WindowFlags flags;
    };
}

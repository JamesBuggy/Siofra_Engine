#pragma once

#include <string>
#include <memory>
#include "core/assertions.hpp"

namespace siofraEngine::platform
{
    /**
     * @brief Wraps plaftorm specific window logic
     */
    class Window
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
        Window(std::string title, int x, int y, int width, int height);

        /**
         * @brief Window destructor
         */
        ~Window();

    private:

        /**
         * @brief Wraps plaftorm specific window state
         */
        class InternalWindow;

        /**
         * @brief Plaftorm specific window state
         */
        std::unique_ptr<InternalWindow> _internalWindow;
    };
}

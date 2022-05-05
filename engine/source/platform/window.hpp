#pragma once

#include <string>
#include <memory>
#include "core/assertions.hpp"

namespace siofraEngine::platform
{
    class Window
    {
    public:
        Window(std::string title, int x, int y, int width, int height);
        ~Window();

    private:
        class InternalWindow;
        std::unique_ptr<InternalWindow> _internalWindow;
    };
}
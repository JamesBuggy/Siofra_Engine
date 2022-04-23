#pragma once

#include <string>
#include <memory>
#include "defines.hpp"
#include "core/assertions.hpp"

namespace engine::platform
{
    class Window
    {
    public:
        Window(std::string title, int x, int y, int width, int height);
        ~Window();

        bool shouldClose();
        void pollEvents();

    private:
        class InternalWindow;
        std::unique_ptr<InternalWindow> _internalWindow;
        bool _shouldClose;
    };
}
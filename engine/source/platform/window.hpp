#pragma once

#include <memory>
#include "defines.hpp"
#include "core/assertions.hpp"

namespace engine::platform
{
    class SE_API Window
    {
    public:
        Window(char const * title, int x, int y, int width, int height);
        ~Window();

        bool shouldClose();
        void pollEvents();

    private:
        class InternalWindow;
        std::unique_ptr<InternalWindow> _internalWindow;
        bool _shouldClose;
    };
}
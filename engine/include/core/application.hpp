#pragma once

#include "defines.hpp"
#include "core/logging.hpp"
#include "platform/platform.hpp"
#include "platform/window.hpp"

namespace engine::core
{
    class SE_API Application
    {
    public:
        Application();
        ~Application();

        void execute();

    private:
        engine::platform::Window window;
    };
}

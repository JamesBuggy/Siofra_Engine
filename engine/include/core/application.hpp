#pragma once

#include <memory>
#include "defines.hpp"
#include "core/logging.hpp"
#include "platform/platform.hpp"
#include "platform/window.hpp"
#include "core/game.hpp"

namespace engine::core
{
    class SE_API Application
    {
    public:
        Application(std::unique_ptr<engine::core::Game> game);
        ~Application();

        void execute();

    private:
        engine::platform::Window window;
        std::unique_ptr<engine::core::Game> game;
    };
}

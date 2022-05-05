#pragma once

#include <memory>
#include "defines.hpp"
#include "platform/platform.hpp"
#include "platform/window.hpp"
#include "core/logging.hpp"
#include "core/game.hpp"
#include "systems/input.hpp"

namespace siofraEngine::core
{
    class SE_API Application
    {
    public:
        Application(std::unique_ptr<siofraEngine::core::Game> game);
        ~Application();

        void execute();

    private:
        siofraEngine::systems::Input inputSystem;
        siofraEngine::platform::Window window;
        std::unique_ptr<siofraEngine::core::Game> game;
    };
}

#pragma once

#include <memory>
#include "defines.hpp"
#include "platform/window.hpp"
#include "platform/platform.hpp"
#include "platform/platformInput.hpp"
#include "platform/platformClock.hpp"
#include "core/logging.hpp"
#include "core/game.hpp"
#include "core/clock.hpp"
#include "systems/input.hpp"

namespace siofraEngine::core
{
    /**
     * @brief Application layer. Controls the application update loop
     */
    class SE_API Application
    {
    public:
        /**
         * @brief Application constructor
         * 
         * @param game Instanse of game to execute
         */
        Application(std::unique_ptr<siofraEngine::core::Game> game);
        
        /**
         * @brief Application destructor
         */ 
        ~Application();

        /**
         * @brief Begin the application update loop
         */
        void execute();

    private:
        /**
         * @brief Input system instance
         */
        siofraEngine::systems::Input inputSystem;

        /**
         * @brief Window instance
         */
        siofraEngine::platform::Window window;

        /**
         * @brief Application closk instance
         */
        siofraEngine::core::Clock clock;

        /**
         * @brief Current game instance
         */
        std::unique_ptr<siofraEngine::core::Game> game;
    };
}

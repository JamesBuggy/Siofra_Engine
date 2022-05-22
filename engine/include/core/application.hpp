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
#include "core/applicationBase.hpp"
#include "systems/input/input.hpp"
#include "systems/renderer/renderer.hpp"

namespace siofraEngine::core
{
    /**
     * @brief Application layer. Controls the application update loop
     */
    class SE_API Application : public ApplicationBase
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
        ~Application() = default;

        /**
         * @brief Begin the application update loop
         */
        void execute() override;

    private:
        /**
         * @brief Application closk instance
         */
        siofraEngine::core::Clock clock;

        /**
         * @brief Window instance
         */
        siofraEngine::platform::Window window;

        /**
         * @brief Input system instance
         */
        siofraEngine::systems::Input inputSystem;

        /**
         * @brief Renderer system instance
         */
        siofraEngine::systems::Renderer rendererSystem;

        /**
         * @brief Current game instance
         */
        std::unique_ptr<siofraEngine::core::Game> game;
    };
}

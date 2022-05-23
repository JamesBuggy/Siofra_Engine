#pragma once

#include "core/application.hpp"
#include "core/applicationBase.hpp"
#include "core/logging.hpp"
#include "core/clock.hpp"
#include "systems/input/input.hpp"
#include "systems/renderer/renderer.hpp"
#include "platform/window.hpp"
#include "platform/platform.hpp"
#include "platform/platformInput.hpp"
#include "platform/platformClock.hpp"

namespace siofraEngine::core
{
    /**
     * @brief Internal application layer implementation
     */
    class Application::Impl : public ApplicationBase
    {
    public:
        /**
         * @brief Application implementation constructor
         * 
         * @param game Instance of game to execute
         */
        Impl(std::unique_ptr<siofraEngine::core::Game> game);

        /**
         * @brief Begin the application update loop
         */
        void execute() override;
    
    private:
        /**
         * @brief Application clock instance
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

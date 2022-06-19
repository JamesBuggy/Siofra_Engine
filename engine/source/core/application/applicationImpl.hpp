#pragma once

#include "core/application.hpp"
#include "core/application/applicationBase.hpp"
#include "core/logging.hpp"
#include "core/clock.hpp"
#include "systems/input/inputSystem.hpp"
#include "systems/renderer/rendererSystem.hpp"
#include "systems/resource/resourceSystem.hpp"
#include "systems/ecs/entityComponent.hpp"
#include "platform/window.hpp"
#include "platform/platform.hpp"
#include "platform/platformInput.hpp"
#include "platform/platformClock.hpp"
#include "platform/platformFileSystem.hpp"

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
        Impl(std::unique_ptr<core::Game> game);

        /**
         * @brief Begin the application update loop
         */
        void execute() override;
    
    private:
        /**
         * @brief Application clock instance
         */
        core::Clock clock;

        /**
         * @brief Window instance
         */
        platform::Window window;

        /**
         * @brief Input system instance
         */
        systems::InputSystem inputSystem;

        /**
         * @brief Renderer system instance
         */
        systems::RendererSystem rendererSystem;

        /**
         * @brief Renderer system instance
         */
        systems::ResourceSystem resourceSystem;

        /**
         * @brief Entity component system
         */
        systems::EntityComponentSystem entityComponentSystem;

        /**
         * @brief Current game instance
         */
        std::unique_ptr<core::Game> game;
    };
}

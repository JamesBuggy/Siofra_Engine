#pragma once

#include <memory>
#include <string>
#include "defines.hpp"
#include "core/logging.hpp"
#include "core/ecs/scene.hpp"
#include "core/ecs/isceneController.hpp"

namespace siofraEngine::core
{
    /**
     * @brief Defines a games behaviour
     */
    class SE_API Game
    {
    public:
        /**
         * @brief Game constructor
         * 
         * @param title Game title
         */
        Game(std::string title);

        /**
         * @brief Game destructor
         */
        virtual ~Game();

        /**
         * @brief Get game title
         * 
         * @returns The game title
         */
        std::string getTitle() const noexcept;

        /**
         * @brief Get game scene
         *
         * @returns The game scene
         */
        Scene * getScene() noexcept;

        /**
         * @brief Get game scene controller
         *
         * @returns The game scene controller
         */
        ISceneController * getSceneController() noexcept;

        /**
         * @brief Set game scene controller
         *
         * @param The game scene controller
         */
        void setSceneController(std::unique_ptr<ISceneController> sceneController) noexcept;

        /**
         * @brief Initialize the game state
         */
        virtual void init() = 0;

        /**
         * @brief Update the game state
         */
        virtual void update() = 0;

    private:
        /**
         * @brief Game internal implementation
         */
        class Impl;

        /**
         * @brief Access to the game internal implementation
         */
        std::unique_ptr<Impl> implementation{ };
    };
}
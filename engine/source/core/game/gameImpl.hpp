#pragma once

#include <string>
#include "core/game.hpp"
#include "core/ecs/scene.h"
#include "core/logging.hpp"

namespace siofraEngine::core
{
    /**
     * @brief Internal game implementation
     */
    class Game::Impl
    {
    public:

        /**
         * @brief Game implementation constructor
         *
         * @param title Game title
         */
        Impl(std::string title);

        /**
         * @brief Game implementation destructor
         */
        ~Impl() = default;

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
        Scene & getScene() noexcept;

    private:
        /**
         * @brief The game title
         */
        std::string title{ };

        /**
         * @brief Game scene
         */
        Scene scene{ };
    };
}

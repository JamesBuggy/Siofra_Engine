#pragma once

#include <string>
#include "defines.hpp"
#include "core/logging.hpp"

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
        virtual ~Game() = default;

        /**
         * @brief Get game title
         * 
         * @returns The game title
         */
        virtual std::string getTitle() const noexcept;

        /**
         * @brief Update the game state
         */
        virtual void update() = 0;

    private:
        /**
         * @brief The game title
         */
        std::string title;
    };
}
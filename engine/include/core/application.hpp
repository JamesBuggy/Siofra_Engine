#pragma once

#include <memory>
#include "defines.hpp"
#include "core/game.hpp"

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
         * @param game Instance of game to execute
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
         * @brief Application internal implementation
         */
        class Impl;

        /**
         * @brief Access to the application internal implementation
         */
        std::unique_ptr<Impl> implementation;
    };
}

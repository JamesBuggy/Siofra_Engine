#pragma once

#include <string>
#include "defines.hpp"
#include "core/logging.hpp"

namespace engine::core
{
    class SE_API Game
    {
    public:
        Game(std::string title);
        virtual ~Game() = default;

        virtual std::string getTitle() const noexcept;

        virtual void update() = 0;

    private:
        std::string title;
    };
}
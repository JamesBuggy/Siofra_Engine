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

        std::string getTitle();

    private:
        std::string title;
    };
}
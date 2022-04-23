#pragma once

#include <string>
#include <core/game.hpp>

class TestGame : public engine::core::Game
{
public:
    TestGame(std::string title);

    void update() override;
};

#pragma once

#include <string>
#include <core/game.hpp>

class TestGame : public siofraEngine::core::Game
{
public:
    TestGame(std::string title);

    void update() override;
};

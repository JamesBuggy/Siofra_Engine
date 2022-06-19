#pragma once

#include <string>
#include <core/game.hpp>
#include <core/logging.hpp>

class TestGame : public siofraEngine::core::Game
{
public:
    TestGame(std::string title);

    void init() override;

    void update() override;
};

#include <engineMain.hpp>
#include "testGame.hpp"

std::unique_ptr<engine::core::Game> createGame()
{
    return std::make_unique<TestGame>("Test Game");
}

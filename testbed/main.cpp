#include <engineMain.hpp>

std::unique_ptr<engine::core::Game> createGame()
{
    return std::make_unique<engine::core::Game>("Test Title");
}
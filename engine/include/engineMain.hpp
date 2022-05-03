#include <core/assertions.hpp>
#include <core/application.hpp>
#include <core/game.hpp>

std::unique_ptr<siofraEngine::core::Game> createGame();

int main()
{
    auto game(createGame());
    SE_ASSERT_TRUE(game.get() != nullptr, "Failed to create game instance");

    siofraEngine::core::Application application(std::move(game));

    application.execute();
}
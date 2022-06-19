#include "testGame.hpp"

TestGame::TestGame(std::string title) :
    Game{title}
{

}

void TestGame::init()
{
    SE_LOG_INFO("Game Init");

    auto scene = getScene();
    auto entityA = scene.addEntity();
    auto entityB = scene.addEntity();

    scene.addComponent<int>(entityA);
    scene.addComponent<int>(entityB);

    auto test = scene.getEntities<int>();
}

void TestGame::update()
{

}

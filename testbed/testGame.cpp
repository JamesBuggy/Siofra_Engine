#include "testGame.hpp"
#include <core/ecs/components.h>

TestGame::TestGame(std::string title) :
    Game{title}
{

}

void TestGame::init()
{
    SE_LOG_INFO("Game Init");

    auto & scene = getScene();
    auto entityA = scene.addEntity();

    auto model = scene.addComponent<siofraEngine::core::Model>(entityA);
    auto material = scene.addComponent<siofraEngine::core::Material>(entityA);

    model->filename = "chair";
    material->filename = "wood_quartered_chiffon";
    scene.addComponent<siofraEngine::core::ModelUpdated>(entityA);
    scene.addComponent<siofraEngine::core::MaterialUpdated>(entityA);
}

void TestGame::update()
{

}

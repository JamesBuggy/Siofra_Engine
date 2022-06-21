#include "testGame.hpp"
#include <core/ecs/components.hpp>

TestGame::TestGame(std::string title) :
    Game{title}
{

}

void TestGame::init()
{
    SE_LOG_INFO("Game Init");

    createEntity("chair", "wood_quartered_chiffon", { 1.0f, 0.0f, 5.0f }, 0.0f);
    createEntity("chair", "wood_quartered_chiffon", { 0.0f, 0.0f, 5.0f }, 45.0f);

    auto scene = getScene();
    auto camera = scene->addEntity();
    scene->addComponent<siofraEngine::core::Camera>(camera);
    auto transform = scene->addComponent<siofraEngine::core::Transform>(camera);

    setSceneController(std::make_unique<TestSceneController>());
}

void TestGame::update()
{

}

void TestGame::createEntity(std::string modelName, std::string materialName, Vector3 position, float angle)
{
    auto scene = getScene();
    auto entity = scene->addEntity();

    auto model = scene->addComponent<siofraEngine::core::Model>(entity);
    auto material = scene->addComponent<siofraEngine::core::Material>(entity);
    auto transform = scene->addComponent<siofraEngine::core::Transform>(entity);
    auto rotation = scene->addComponent<siofraEngine::core::Rotation>(entity);
    scene->addComponent<siofraEngine::core::ModelUpdated>(entity);
    scene->addComponent<siofraEngine::core::MaterialUpdated>(entity);

    model->filename = modelName;
    material->filename = materialName;
    transform->position = position;
    rotation->angle = angle;
}

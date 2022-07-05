#include "testGame.hpp"
#include <core/ecs/components.hpp>

TestGame::TestGame(std::string title) :
    Game{title}
{

}

void TestGame::init()
{
    SE_LOG_INFO("Game Init");

    createEntity("chair", "wood_quartered_chiffon", { 2.5f, 0.0f, 2.5f }, { 0.0f, 30.0f, 0.0f });
    createEntity("chair", "wood_quartered_chiffon", { 1.0f, 0.0f, 2.5f }, { 0.0f, 180.0f, 0.0f });

    for (float x{ 0.0f }; x < 5.0f; ++x)
    {
        for (float z{ 0.0f }; z < 5.0f; ++z)
        {
            createEntity("plane", "wood_floor_tilling", { x, 0.0f, z }, { 0.0f, 0.0f, 0.0f });
        }
    }

    for (float y{ 0.5f }; y < 2.0f; ++y)
    {
        for (float xz{ 0.0f }; xz < 5.0f; ++xz)
        {
            createEntity("plane", "stone_wall_tilling", { xz, y, 4.5f }, { -90.0f, 0.0f, 0.0f });
            createEntity("plane", "stone_wall_tilling", { 4.5f, y, xz }, { 90.0f, 0.0f, 90.0f });
        }
    }

    auto scene = getScene();
    auto camera = scene->addEntity();
    scene->addComponent<siofraEngine::core::Camera>(camera);
    auto transformComponent = scene->addComponent<siofraEngine::core::Transform>(camera);
    transformComponent->position.y = 1.0f;

    setSceneController(std::make_unique<TestSceneController>());
}

void TestGame::update()
{

}

void TestGame::createEntity(std::string modelName, std::string materialName, siofraEngine::math::Vector3 position, siofraEngine::math::Vector3 rotation)
{
    auto scene = getScene();
    auto entity = scene->addEntity();

    auto modelComponent = scene->addComponent<siofraEngine::core::Model>(entity);
    auto materialComponent = scene->addComponent<siofraEngine::core::Material>(entity);
    auto transformComponent = scene->addComponent<siofraEngine::core::Transform>(entity);
    auto rotationComponent = scene->addComponent<siofraEngine::core::Rotation>(entity);
    scene->addComponent<siofraEngine::core::ModelUpdated>(entity);
    scene->addComponent<siofraEngine::core::MaterialUpdated>(entity);

    modelComponent->filename = modelName;
    materialComponent->filename = materialName;
    transformComponent->position = position;
    rotationComponent->angles = rotation;
}

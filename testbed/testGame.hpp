#pragma once

#include <string>
#include <core/game.hpp>
#include <core/logging.hpp>
#include <math/math.hpp>
#include "testSceneController.hpp"

class TestGame : public siofraEngine::core::Game
{
public:
    TestGame(std::string title);

    void init() override;

    void update() override;

    void createEntity(std::string modelName, std::string materialName, siofraEngine::math::Vector3 position, float angle);
};

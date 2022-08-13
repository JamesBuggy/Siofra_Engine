#pragma once

#include <string>
#include <algorithm>
#include <core/logging.hpp>
#include <core/ecs/isceneController.hpp>
#include <core/ecs/scene.hpp>
#include <core/ecs/components.hpp>
#include <core/input/iinputState.hpp>

class TestSceneController : public siofraEngine::core::ISceneController
{
public:
    void init(siofraEngine::core::Scene * scene) override;

    void update(siofraEngine::core::IInputState const * inputState, siofraEngine::core::Scene * scene, float deltaTime) override;

private:
    siofraEngine::core::Entity cameraEntity{ };
    siofraEngine::core::Transform * camerTransform{ };
    siofraEngine::core::Camera * camerCamera{ };
};

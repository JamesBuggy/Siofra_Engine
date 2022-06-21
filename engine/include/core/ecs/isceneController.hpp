#pragma once

#include "defines.hpp"
#include "core/ecs/scene.hpp"
#include "core/input/iinputState.hpp"

namespace siofraEngine::core
{
    class SE_API ISceneController
    {
    public:

        virtual void init(Scene * scene) = 0;

        virtual void update(IInputState const * inputState, Scene * scene, float deltaTime) = 0;

        virtual ~ISceneController() = default;
    };
}

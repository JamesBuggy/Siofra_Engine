#pragma once

#include "core/ecs/scene.hpp"
#include "systems/events/ieventSystem.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Audio system. Handles audio playback
     */
    class AudioSystem
    {
    public:
        /**
         * @brief AudioSystem constructor
         *
         */
        AudioSystem(IEventSystem* const eventSystem);

        /**
         * @brief Update the scenes audio state
         *
         * @param scene The ECS scene to update
         */
        void update(core::Scene* scene);

    private:
        /**
         * @brief Event system
         */
        systems::IEventSystem* const eventSystem;
    };
}
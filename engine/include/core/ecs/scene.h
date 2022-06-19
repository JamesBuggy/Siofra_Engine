#pragma once

#include <vector>
#include "defines.hpp"
#include "core/ecs/types.hpp"
#include "systems/ecs/entityComponent.hpp"

namespace siofraEngine::core
{
    /**
    * @brief Maintains an ECS containing the entities which have been added to the scene
    */
    class SE_API Scene
    {
    public:
        /**
         * @brief Add a new entity to the scene
         *
         * @returns The newly added entity
         */
        core::Entity addEntity()
        {
            return entityComponentSystem.activateEntity();
        }

        /**
         * @brief Remove an entity from the scene
         *
         * @param entity The entity to remove from the scene
         * @returns True if the entity was removed, otherwise false
         */
        bool removeEntity(core::Entity entity)
        {
            return entityComponentSystem.deactivateEntity(entity);
        }

        /**
         * @brief Get a list of all entities present in the scene
         *
         * @returns The list of all entities present in the scene
         */
        std::vector<core::Entity> const& getEntities() const noexcept
        {
            return entityComponentSystem.getActiveEntities();
        }

        /**
         * @brief Attach a component to an entity
         *
         * @tparam T The type of the component to attach
         * @param entity The entity to attach the component to
         * @returns A pointer to the attached component
         */
        template<typename T>
        T * addComponent(core::Entity entity)
        {
            return entityComponentSystem.assignComponent<T>(entity);
        }

        /**
         * @brief Remove a component from an entity
         *
         * @tparam T The type of the component to remove
         * @param entity The entity to remove the component from
         * @returns True if the component was removed, otherwise false
         */
        template<typename T>
        bool removeComponent(core::Entity entity) noexcept
        {
            return entityComponentSystem.removeComponent<T>(entity);
        }

        /**
         * @brief Get a component which is attahced to an entity
         *
         * @tparam T The type of the component to get
         * @param entity The entity to retrieve the component from
         * @returns A pointer to the retrieved component
         */
        template<typename T>
        T * getComponent(core::Entity entity)
        {
            return entityComponentSystem.getComponent<T>(entity);
        }

    private:
        /**
         * @brief The ECS containing all entities present in the scene
         */
        systems::EntityComponentSystem entityComponentSystem{ };
    };
}

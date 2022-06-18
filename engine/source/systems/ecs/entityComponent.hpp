#pragma once

#include <bitset>
#include <map>
#include "systems/ecs/entityManager/entityManager.hpp"
#include "systems/ecs/componentManager/componentManager.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Bitset describing the components attached to an entity
     */
    using EntityComponentSignature = std::bitset<ComponentManager::MAX_COMPONENT_COUNT>;

    /**
     * @brief Entity component system. Maintains entities, component pool and assignment of components to entities 
     */
    class EntityComponentSystem
    {
    public:
        /**
         * @brief Activate a new entity
         * 
         * @returns The newly activated entity
         */
        Entity activateEntity() noexcept
        {
            Entity newEntity = entityManager.activateEntity();
            if(newEntity != EntityManager::INVALID_ENTITY)
            {
                entityComponentSignatures[newEntity] = EntityComponentSignature{ 0 };
            }
            return newEntity;
        }

        /**
         * @brief Dectivate an active entity
         * 
         * @param entity The currently active entity to deactivate
         */
        void deactivateEntity(Entity entity) noexcept
        {
            bool result = entityManager.deactivateEntity(entity);
            if(result)
            {
                entityComponentSignatures.erase(entity);
            }
        }

        /**
         * @brief Get a list of all currently active entities
         * 
         * @returns A list of all currently active entities
         */
        std::vector<Entity> const & getActiveEntities() const noexcept
        {
            return entityManager.getActiveEntities();
        }

        /**
         * @brief Assign a component to an entity
         * 
         * @tparam T The component type to assign to the entity
         * @param entity The entity to which the component should be assigned
         * @returns A pointer to the assigned component, or nullptr if assignment failed
         */
        template<typename T>
        T * assignComponent(Entity entity)
        {
            auto componentId = componentManager.getComponentTypeId<T>();
            if (componentId == ComponentManager::INVALID_COMPONENT)
            {
                SE_LOG_WARNING("Failed to register new component type. Maximum component count reached");
                return nullptr;
            }

            if(!entityComponentSignatures.count(entity))
            {
                SE_LOG_WARNING("Cannot assign component to inactive entity");
                return nullptr;
            }

            auto newComponent = componentManager.assignComponent<T>(entity);
            if(!newComponent)
            {
                SE_LOG_WARNING("Failed to assign component");
                return nullptr;
            }

            entityComponentSignatures[entity].set(componentId);
            return newComponent;
        }

        /**
         * @brief Remove a component from an entity. The component type will be registered with the ECS if it has not been already
         * 
         * @tparam T The component type to remove from the entity
         * @param entity The entity from which the component should be removed
         * @returns True if the component was removed, otherwise false
         */
        template<typename T>
        bool removeComponent(Entity entity) noexcept
        {
            auto componentId = componentManager.getComponentTypeId<T>();
            if (componentId == ComponentManager::INVALID_COMPONENT)
            {
                SE_LOG_WARNING("Failed to remove component. Invalid component specified");
                return false;
            }

            if(!entityComponentSignatures.count(entity))
            {
                SE_LOG_WARNING("Failed to remove component. Cannot remove component from inactive entity");
                return false;
            }
            
            entityComponentSignatures[entity].reset(componentId);
            return true;
        }

        /**
         * @brief Get a component assigned to an entity. The component type will be registered with the ECS if it has not been already
         * 
         * @tparam T The component type to get from the entity
         * @param entity The entity for which to retrieve the component
         * @returns A pointer to the component, or nullptr if the retrieval failed
         */
        template<typename T>
        T * getComponent(Entity entity)
        {
            auto componentId = componentManager.getComponentTypeId<T>();
            if (componentId == ComponentManager::INVALID_COMPONENT)
            {
                SE_LOG_WARNING("Failed to get component. Invalid component specified");
                return nullptr;
            }

            if(!entityComponentSignatures.count(entity))
            {
                SE_LOG_WARNING("Cannot get component of inactive entity");
                return nullptr;
            }

            if(!entityComponentSignatures[entity].test(componentId))
            {
                SE_LOG_WARNING("Failed to get component. Specfied entity does not have to specified component");
                return nullptr;
            }

            return componentManager.getComponent<T>(entity);
        }
    
    private:
        /**
         * @brief Entity manager. Maintains collections of active and available entity Ids
         */
        EntityManager entityManager{ };

        /**
         * @brief Component manager. Maintains component memory pools and component Ids
         */
        ComponentManager componentManager{ EntityManager::MAX_ENTITY_COUNT };

        /**
         * @brief Mapping of active entity Ids to their component signatures
         */
        std::map<Entity, EntityComponentSignature> entityComponentSignatures{ };
    };
}

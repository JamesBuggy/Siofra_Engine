#pragma once

#include <bitset>
#include <map>
#include "systems/ecs/entityManager/entityManager.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Bitset describing the components attached to an entity
     */
    using EntityComponentSignature = std::bitset<32>;

    /**
     * @brief Entity component system. Maintains entities, component pool and assignment of components to entities 
     */
    class EntityComponentSystem
    {
    public:
        /**
         * @brief EntityComponentSystem constructor
         */
        EntityComponentSystem();

        /**
         * @brief Activate a new entity
         * 
         * @returns The newly activated entity
         */
        Entity activateEntity() noexcept;

        /**
         * @brief Dectivate an active entity
         * 
         * @param entity The currently active entity to deactivate
         */
        void deactivateEntity(Entity entity) noexcept;

        /**
         * @brief Get a list of all currently active entities
         * 
         * @returns A list of all currently active entities
         */
        std::vector<Entity> const & getActiveEntities() const noexcept;
    
    private:
        /**
         * @brief Entity manager. Maintains collections of active and available entity Ids
         */
        EntityManager entityManager{ };

        /**
         * @brief Mapping of active entity Ids to their component signatures
         */
        std::map<Entity, EntityComponentSignature> entityComponentSignatures{ };
    };
}

#pragma once

#include <cstdint>
#include <vector>
#include <deque>
#include <limits>
#include <algorithm>
#include "core/logging.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Entity type
     */
    using Entity = std::uint32_t;

    /**
     * @brief Entity manager. Maintains collections of active and available entity Ids
     */
    class EntityManager
    {
    public:
        /**
         * @brief EntityManager. Initializes the inactive entity collection based on the maximum entity count
         */
        EntityManager();

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
         * @returns True if the entity was deactivated, otherwise false
         */
        bool deactivateEntity(Entity entity) noexcept;

        /**
         * @brief Get a list of all currently active entities
         * 
         * @returns A list of all currently active entities
         */
        std::vector<Entity> const & getActiveEntities() const noexcept;

        /**
         * @brief Maximum number of entities supported
         */
        static inline std::uint32_t const MAX_ENTITY_COUNT{ 1000 };

        /**
         * @brief Invalid entity identifier
         */
        static inline Entity const INVALID_ENTITY{ std::numeric_limits<Entity>::max() };
    
    private:
        /**
         * @brief Collection of active entities
         */
        std::vector<Entity> activeEntities{ };

        /**
         * @brief Collection of available (inactive) entities. Entities are popped off of the front on creation and pushed to the back on deletion
         */
        std::deque<Entity> availableEntities{ };
    };
}

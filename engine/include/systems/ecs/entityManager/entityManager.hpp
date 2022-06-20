#pragma once

#include <cstdint>
#include <vector>
#include <deque>
#include <algorithm>
#include "defines.hpp"
#include "core/logging.hpp"
#include "core/ecs/types.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Entity manager. Maintains collections of active and available entity Ids
     */
    class SE_API EntityManager
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
        core::Entity activateEntity() noexcept;

        /**
         * @brief Dectivate an active entity
         * 
         * @param entity The currently active entity to deactivate
         * @returns True if the entity was deactivated, otherwise false
         */
        bool deactivateEntity(core::Entity entity) noexcept;

        /**
         * @brief Get a list of all currently active entities
         * 
         * @returns A list of all currently active entities
         */
        std::vector<core::Entity> const & getActiveEntities() const noexcept;

        /**
         * @brief Maximum number of entities supported
         */
        static inline std::uint32_t const MAX_ENTITY_COUNT{ 1000 };
    
    private:
        /**
         * @brief Collection of active entities
         */
        std::vector<core::Entity> activeEntities{ };

        /**
         * @brief Collection of available (inactive) entities. Entities are popped off of the front on creation and pushed to the back on deletion
         */
        std::deque<core::Entity> availableEntities{ };
    };
}

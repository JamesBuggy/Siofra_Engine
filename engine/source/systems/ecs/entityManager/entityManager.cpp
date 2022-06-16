#include "systems/ecs/entityManager/entityManager.hpp"

namespace siofraEngine::systems
{
    EntityManager::EntityManager()
    {
        activeEntities.reserve(MAX_ENTITY_COUNT);
        for(Entity entity{ 0 }; entity < MAX_ENTITY_COUNT; ++entity)
        {
            availableEntities.push_back(entity);
        }
    }

    Entity EntityManager::activateEntity() noexcept
    {
        if(!availableEntities.empty())
        {
            activeEntities.push_back(availableEntities.front());
            availableEntities.pop_front();
            return activeEntities.back();
        }

        SE_LOG_WARNING("Failed to activate entity. Maximun entity count reached");
        return INVALID_ENTITY;
    }

    bool EntityManager::deactivateEntity(Entity entity) noexcept
    {
        auto entityIter = std::find(activeEntities.begin(), activeEntities.end(), entity);
        if(entityIter != activeEntities.end())
        {
            activeEntities.erase(entityIter, entityIter + 1);
            availableEntities.push_back(entity);
            return true;
        }
        
        SE_LOG_WARNING("Failed to deactivate entity. Cannot deactivate inactive entity");
        return false;
    }

    std::vector<Entity> const & EntityManager::getActiveEntities() const noexcept
    {
        return activeEntities;
    }
}

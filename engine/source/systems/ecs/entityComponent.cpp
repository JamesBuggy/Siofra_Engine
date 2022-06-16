#include "systems/ecs/entityComponent.hpp"

namespace siofraEngine::systems
{
    EntityComponentSystem::EntityComponentSystem()
    {
        
    }

    Entity EntityComponentSystem::activateEntity() noexcept
    {
        Entity newEntity = entityManager.activateEntity();
        if(newEntity != EntityManager::INVALID_ENTITY)
        {
            entityComponentSignatures[newEntity] = EntityComponentSignature{ 0 };
        }
        return newEntity;
    }

    void EntityComponentSystem::deactivateEntity(Entity entity) noexcept
    {
        bool result = entityManager.deactivateEntity(entity);
        if(result)
        {
            entityComponentSignatures.erase(entity);
        }
    }

    std::vector<Entity> const & EntityComponentSystem::getActiveEntities() const noexcept
    {
        return entityManager.getActiveEntities();
    }
}

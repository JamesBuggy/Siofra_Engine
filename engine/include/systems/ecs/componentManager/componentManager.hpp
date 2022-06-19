#pragma once

#include <array>
#include <cstdint>
#include <limits>
#include <vector>
#include "defines.hpp"
#include "core/logging.hpp"
#include "core/ecs/types.hpp"

namespace siofraEngine::systems
{    
    /**
     * @brief Component manager. Maintains component memory pools
     */
    class SE_API ComponentManager
    {
    public:
        /**
         * @brief Component constructor
         * 
         * @param maxEntities The maximum nuber of entites supported by the ECS
         */
        ComponentManager(std::uint32_t maxEntities) :
            maxEntities{maxEntities}
        {
            componentPools.reserve(MAX_COMPONENT_COUNT);
        }

        /**
         * @brief Assign a component to an entity
         * 
         * @tparam T The component type to assign to the entity
         * @param entity The entity to which the component should be assigned
         * @returns A pointer to the assigned component
         */
        template<typename T>
        T * assignComponent(core::Entity entity)
        {
            std::uint32_t componentId = getComponentTypeId<T>();
            if (componentId == componentPools.size())
            {
                size_t componentSize = sizeof(T);
                componentPools.push_back(std::vector<char>(componentSize * maxEntities));
                componentSizes.push_back(componentSize);
            }

            auto componentAddress = componentPools[componentId].data() + (entity * componentSizes[componentId]);
            return new (componentAddress) T();
        }

        /**
         * @brief Get a component assigned to an entity
         * 
         * @tparam T The component type to get from the entity
         * @param entity The entity for which to retrieve the component
         * @returns A pointer to the component
         */
        template<typename T>
        T * getComponent(core::Entity entity)
        {
            std::uint32_t componentId = getComponentTypeId<T>();
            return reinterpret_cast<T*>(componentPools[componentId].data() + (entity * componentSizes[componentId]));
        }

        /**
         * @brief Get the Id assigned to a component type. An Id will be assigned if one has not been already
         * 
         * @tparam T The component type for which to get an Id
         * @returns The Id for the given component type
         */
        template <typename T>
        std::uint32_t getComponentTypeId()
        {
            if(componentTypeCount < MAX_COMPONENT_COUNT)
            {
                static std::uint32_t componentTypeId = componentTypeCount++;
                return componentTypeId;
            }

            return core::INVALID_COMPONENT;
        }

        /**
         * @brief Maximum number of components per entity
         */
        static inline std::uint32_t const MAX_COMPONENT_COUNT{ 32 };   
    
    private:
        /**
         * @brief Component memory pools. One per component type
         */
        std::vector<std::vector<char>> componentPools{ };

        /**
         * @brief The sizes, in bytes, of components stored in the component pools. There is a one to one relationship between componentSizes and componentPools. Used to allow indexing into a specific component pool
         */
        std::vector<size_t> componentSizes{ };

        /**
         * @brief The maximum nuber of entites supported by the ECS. Used to determine maximun required component pool size
         */
        std::uint32_t maxEntities{ };

        /**
         * @brief The number of component types which have been given an Id. Incremented each time a new component type is given an Id
         */
        static inline std::uint32_t componentTypeCount{ 0 };
    };
}

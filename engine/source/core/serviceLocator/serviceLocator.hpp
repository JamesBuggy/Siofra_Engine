#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include "core/logging.hpp"

namespace siofraEngine::core
{
    /**
     * @brief Service locator primarly for used by classes implementing the pimpl pattern to access internal engine functionality
     */
	class ServiceLocator
	{
	public:
        /**
         * @brief Register a type to be provided by the service locator. An instance of the type is default constructed and stored within the service locator
         * 
         * @tparam T The type of the object to provided
         */
        template<typename T>
        static void provide()
        {
            std::uint32_t serviceId = getServiceTypeId<T>();
            if (services.count(serviceId))
            {
                SE_LOG_WARNING("Service for specfied type already registerd");
                return;
            }
            services[serviceId] = std::vector<char>(sizeof(T));
            new (services[serviceId].data()) T();
        }

        /**
         * @brief Get an object that has been registered with the service provider
         *
         * @tparam T The type of the object to retrieve
         * @returns A pointer to the retrieved object
         */
        template<typename T>
        static T * const get()
        {
            std::uint32_t serviceId = getServiceTypeId<T>();
            return reinterpret_cast<T*>(services[serviceId].data());
        }

	private:
        /**
         * @brief Get the Id assigned to a type which has been registered with the service locator. An Id will be assigned if one has not been already
         *
         * @tparam T The type for which to get an Id
         * @returns The Id for the given type
         */
        template <typename T>
        static std::uint32_t getServiceTypeId()
        {
            static std::uint32_t serviceTypeId = serviceTypeCount++;
            return serviceTypeId;
        }

        /**
         * @brief The number of types which have been given an Id. Incremented each time a new type is given an Id
         */
        static inline std::uint32_t serviceTypeCount{ 0 };

        /**
         * @brief Collection of types registered with the service locator, and the object to return for each type
         */
        static inline std::map<std::uint32_t, std::vector<char>> services{ };
	};
}

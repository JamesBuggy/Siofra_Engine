#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include "core/logging.hpp"

namespace siofraEngine::core
{
	class ServiceLocator
	{
	public:
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

        template<typename T>
        static T * const get()
        {
            std::uint32_t serviceId = getServiceTypeId<T>();
            return reinterpret_cast<T*>(services[serviceId].data());
        }

	private:

        template <typename T>
        static std::uint32_t getServiceTypeId()
        {
            static std::uint32_t serviceTypeId = serviceTypeCount++;
            return serviceTypeId;
        }

        static inline std::uint32_t serviceTypeCount{ 0 };

        static inline std::map<std::uint32_t, std::vector<char>> services{ };
	};
}

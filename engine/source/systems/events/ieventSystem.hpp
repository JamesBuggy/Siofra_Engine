#pragma once

#include "systems/events/events.h"

namespace siofraEngine::systems
{
    /**
     * @brief Event system interface
     */
    class IEventSystem
    {
    public:
        /**
         * @brief Broadcast an payload to all subscribers of an event type
         * 
         * @param eventType The event type
         * @param payload The event payload
         */
        virtual void broadcast(EventTypes eventType, EventPayload payload) const = 0;

        /**
         * @brief Subscribe to an event type
         * 
         * @param eventType The event type
         * @param callback The callback to be executed upon broadcast of the specified event type
         */
        virtual void subcsribe(EventTypes eventType, EventCallback callback) noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IEventSystem() = default;
    };
}

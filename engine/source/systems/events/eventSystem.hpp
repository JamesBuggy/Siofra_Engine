#pragma once

#include <map>
#include <vector>
#include <cstdint>
#include "systems/events/ieventSystem.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Event system interface
     */
    class EventSystem : public IEventSystem
    {
    public:
        /**
         * @brief EventSystem constructor
         */
        EventSystem();

        /**
         * @brief Broadcast an payload to all subscribers of an event type
         * 
         * @param eventType The event type
         * @param payload The event payload
         */
        void broadcast(EventTypes eventType, EventPayload payload) const override;

        /**
         * @brief Subscribe to an event type
         * 
         * @param eventType The event type
         * @param callback The callback to be executed upon broadcast of the specified event type
         */
        void subcsribe(EventTypes eventType, EventCallback callback) noexcept override;
    
    private:
        /**
         * @brief A map of subscriptions to each event type
         */
        std::map<EventTypes, std::vector<EventCallback>> eventSubscriptions{ };
    };
}

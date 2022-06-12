#include "systems/events/eventSystem.hpp"

namespace siofraEngine::systems
{
    EventSystem::EventSystem()
    {
        auto eventTypeCount{ static_cast<std::uint32_t>(EventTypes::MAX_EVENT_TYPES) };
        for (size_t i = 0; i < eventTypeCount; ++i)
        {
            eventSubscriptions[static_cast<EventTypes>(i)] = { };
        }
    }

    void EventSystem::broadcast(EventTypes eventType, EventPayload payload) const
    {
        for(auto const & callback : eventSubscriptions.at(eventType))
        {
            callback(payload);
        }
    }

    void EventSystem::subscribe(EventTypes eventType, EventCallback callback) noexcept
    {
        eventSubscriptions[eventType].push_back(callback);
    }
}

#pragma once

#include <functional>
#include <variant>
#include <string>

/**
 * @brief Supported event types
 */
enum class EventTypes
{
    MAX_EVENT_TYPES
};

/**
 * @brief Event payload
 */
using EventPayload = std::variant<
    int,
    bool,
    float,
    double,
    char,
    std::string
>;

/**
 * @brief Event callback
 */
using EventCallback = std::function<void(EventPayload)>;

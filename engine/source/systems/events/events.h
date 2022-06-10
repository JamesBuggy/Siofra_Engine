#pragma once

#include <functional>
#include <variant>
#include <string>
#include <vector>

/**
 * @brief Supported event types
 */
enum class EventTypes
{
    CREATE_SHADER,
    MAX_EVENT_TYPES
};

struct CreateShaderEvent
{
    std::vector<char> vertexStageFileContent;
    std::vector<char> fragmentStageFileContent;
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
    std::string,
    CreateShaderEvent
>;

/**
 * @brief Event callback
 */
using EventCallback = std::function<void(EventPayload)>;

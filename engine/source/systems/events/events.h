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

/**
 * @brief Create shader event payload. Contains shader file content in bytes
 */
struct CreateShaderEvent
{
    /**
     * @brief Vertex stage GLSL file content
     */
    std::vector<char> vertexStageGlsl;

    /**
     * @brief Vertex stage Spir-v file content
     */
    std::vector<char> vertexStageSpirv;

    /**
     * @brief Fragment stage GLSL file content
     */
    std::vector<char> fragmentStageGlsl;

    /**
     * @brief Fragment stage Spir-v file content
     */
    std::vector<char> fragmentStageSpirv;
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

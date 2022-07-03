#pragma once

#include <functional>
#include <variant>
#include <string>
#include <vector>
#include <cstdint>
#include "math/math.hpp"

/**
 * @brief Supported event types
 */
enum class EventTypes
{
    CREATE_SHADER,
    CREATE_MATERIAL,
    CREATE_MODEL,
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
 * @brief Create material event payload
 */
struct CreateMaterialEvent
{
    std::string materialName;
    std::vector<char> imageData;
    std::uint32_t width;
    std::uint32_t height;
    std::uint32_t channels;
};

/**
 * @brief Create model event payload
 */
struct CreateModelEvent
{
    std::string modelName;
    std::vector<siofraEngine::math::Vertex3> vertexBuffer;
    std::vector<std::vector<std::uint32_t>> indexBuffers;
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
    CreateShaderEvent,
    CreateMaterialEvent,
    CreateModelEvent
>;

/**
 * @brief Event callback
 */
using EventCallback = std::function<void(EventPayload)>;

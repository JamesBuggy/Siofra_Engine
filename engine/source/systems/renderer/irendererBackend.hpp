#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include "math/math.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Supported renderer backends
     */
    enum class RendererBackends
    {
        VULKAN
    };

    /**
     * @brief Renderer backend interface
     */
    class IRendererBackend
    {
    public:
        /**
         * @brief Draw current frame
         */
        virtual void draw() = 0;

        /**
         * @brief Get the renderer backend type
         * 
         * @returns The renderer backend type
         */
        virtual RendererBackends getRendererBackendType() const noexcept = 0;

        /**
         * @brief Create a shader
         * 
         * @param vertexShaderCode Vertex shader code bytes
         * @param fragmentShaderCode Fragment shader code bytes
         */
        virtual void createShader(std::vector<char> vertexShaderCode, std::vector<char> fragmentShaderCode) = 0;

        /**
         * @brief Create a shader pipeline
         * 
         * @param materialName The material name
         * @param imageData Image bytes
         * @param width Image width
         * @param height Image height
         * @param channels Image channel count
         */
        virtual void createMaterial(std::string materialName, std::vector<char> imageData, std::uint32_t width, std::uint32_t height, std::uint32_t channels) = 0;

        /**
         * @brief Create a model
         * 
         * @param modelName The model name
         * @param vertexBuffer Model vertices
         * @param indexBuffers Model vertex indices
         */
        virtual void createModel(std::string modelName, std::vector<Vertex3> vertexBuffer, std::vector<std::vector<std::uint32_t>> indexBuffers) = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IRendererBackend() = default;
    };
}

#pragma once

#include <vector>

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
         */
        virtual void createShader(std::vector<char> vertexShaderCode, std::vector<char> fragmentShaderCode) const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IRendererBackend() = default;
    };
}

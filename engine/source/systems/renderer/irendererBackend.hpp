#pragma once

namespace siofraEngine::systems
{
    /**
     * @brief Renderer backend interface
     */
    class IRendererBackend
    {
    public:
        /**
         * @brief Interface destructor
         */
        virtual ~IRendererBackend() = default;
    };
}

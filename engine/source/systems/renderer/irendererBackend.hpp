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
         * @brief Draw current frame
         */
        virtual void draw() = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IRendererBackend() = default;
    };
}

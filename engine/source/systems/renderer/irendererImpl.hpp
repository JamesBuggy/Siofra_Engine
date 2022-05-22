#pragma once

namespace siofraEngine::systems
{
    /**
     * @brief Renderer backend interface
     */
    class IRendererImpl
    {
    public:
        /**
         * @brief Interface destructor
         */
        virtual ~IRendererImpl() = default;
    };
}

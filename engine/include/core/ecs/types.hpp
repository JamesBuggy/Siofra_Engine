#pragma once

#include <cstdint>

namespace siofraEngine::core
{
    /**
     * @brief Entity type
     */
    using Entity = std::uint32_t;

    /**
    * @brief Invalid entity identifier
    */
    static inline Entity const INVALID_ENTITY{ std::numeric_limits<Entity>::max() };

    /**
    * @brief Invalid component identifier
    */
    static inline std::uint32_t const INVALID_COMPONENT{ std::numeric_limits<std::uint32_t>::max() };
}

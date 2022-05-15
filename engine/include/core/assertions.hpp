#pragma once

#include "defines.hpp"
#include <assert.h>
#include "logging.hpp"

namespace siofraEngine::core
{
    /**
     * @brief Provides assertion functionality
     */
    class SE_API Assertions
    {
    public:
        /**
         * @brief Asserts that a condition is true
         */
        static void assertTrue(bool condition, const char* file, int line, const char* message);

    private:
    };
}

#ifdef DEBUG
    #define SE_ASSERT_TRUE(condition, message) \
        siofraEngine::core::Assertions::assertTrue(condition, __FILE__, __LINE__, message)
#else
    #define SE_ASSERT_TRUE(condition, message)
#endif

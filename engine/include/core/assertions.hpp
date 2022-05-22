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
         * 
         * @param condition Condition to test
         * @param file File name
         * @param line Line number
         * @param message Condition failure message
         */
        template<typename T>
        static void assertTrue(bool condition, const char* file, int line, T message)
        {
            if(!condition) {
                Logger::logCritical(file, line, message);
                assert(condition);
            }
        }

    private:
    };
}

#ifdef DEBUG
    #define SE_ASSERT_TRUE(condition, message) \
        siofraEngine::core::Assertions::assertTrue(condition, __FILE__, __LINE__, message)
#else
    #define SE_ASSERT_TRUE(condition, message)
#endif

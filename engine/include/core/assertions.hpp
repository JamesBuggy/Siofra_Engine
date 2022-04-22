#pragma once

#include "defines.hpp"
#include <assert.h>
#include "logging.hpp"

namespace engine::core
{
    class SE_API Assertions
    {
    public:
        static void assertTrue(bool condition, const char* file, int line, const char* message);

    private:
    };
}

#ifdef DEBUG
    #define SE_ASSERT_TRUE(condition, message) \
        engine::core::Assertions::assertTrue(condition, __FILE__, __LINE__, message)
#else
    #define SE_ASSERT_TRUE(condition, message)
#endif

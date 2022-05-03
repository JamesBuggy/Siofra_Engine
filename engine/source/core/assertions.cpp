#include "core/assertions.hpp"

namespace siofraEngine::core
{
    void Assertions::assertTrue(bool condition, const char* file, int line, const char* message)
    {
        if(!condition) {
            Logger::logCritical(file, line, message);
            assert(condition);
        }
    }
}
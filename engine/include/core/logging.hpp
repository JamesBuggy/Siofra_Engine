#pragma once

#include <iostream>
#include <string>
#include "defines.hpp"

namespace siofraEngine::core
{
    class SE_API Logger
    {
    public:
        static void logTrace(const char* file, int line, const char* message);
        static void logDebug(const char* file, int line, const char* message);
        static void logInfo(const char* file, int line, const char* message);
        static void logWarning(const char* file, int line, const char* message);
        static void logError(const char* file, int line, const char* message);
        static void logCritical(const char* file, int line, const char* message);

    private:

        enum class LogLevel
        {
            trace = 0,
            debug = 1,
            info = 2,
            warning = 3,
            error = 4,
            critical = 5,
            none = 6
        };

        static constexpr const char* logLevelStrings[] =
        {
            "TRACE",
            "DEBUG",
            "INFO",
            "WARNING",
            "ERROR",
            "CRITICAL",
            "NONE"
        };

        static void log(LogLevel logLevel, const char* file, int line, const char* message);
    };
}

#ifdef DEBUG
    #define SE_LOG_TRACE(message) \
        siofraEngine::core::Logger::logTrace(__FILE__, __LINE__, message)

    #define SE_LOG_DEBUG(message) \
        siofraEngine::core::Logger::logDebug(__FILE__, __LINE__, message)

    #define SE_LOG_INFO(message) \
        siofraEngine::core::Logger::logInfo(__FILE__, __LINE__, message)

    #define SE_LOG_WARNING(message) \
        siofraEngine::core::Logger::logWarning(__FILE__, __LINE__, message)

    #define SE_LOG_ERROR(message) \
        siofraEngine::core::Logger::logError(__FILE__, __LINE__, message)

    #define SE_LOG_CRITICAL(message) \
        siofraEngine::core::Logger::logCritical(__FILE__, __LINE__, message)
#else
    #define SE_LOG_TRACE(message)
    #define SE_LOG_DEBUG(message)
    #define SE_LOG_INFO(message)
    #define SE_LOG_WARNING(message)
    #define SE_LOG_ERROR(message)
    #define SE_LOG_CRITICAL(message)
#endif
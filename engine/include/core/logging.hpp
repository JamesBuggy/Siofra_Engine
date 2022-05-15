#pragma once

#include <iostream>
#include <string>
#include "defines.hpp"

namespace siofraEngine::core
{
    /**
     * @brief Provides logging functionality
     */
    class SE_API Logger
    {
    public:
        /**
         * @brief Log a trace message
         * 
         * @param file File name
         * @param line Line number
         * @param message Log message
         */
        static void logTrace(const char* file, int line, const char* message);

        /**
         * @brief Log a debug message
         * 
         * @param file File name
         * @param line Line number
         * @param message Log message
         */
        static void logDebug(const char* file, int line, const char* message);

        /**
         * @brief Log an informational message
         * 
         * @param file File name
         * @param line Line number
         * @param message Log message
         */
        static void logInfo(const char* file, int line, const char* message);

        /**
         * @brief Log a warning message
         * 
         * @param file File name
         * @param line Line number
         * @param message Log message
         */
        static void logWarning(const char* file, int line, const char* message);

        /**
         * @brief Log an error message
         * 
         * @param file File name
         * @param line Line number
         * @param message Log message
         */
        static void logError(const char* file, int line, const char* message);

        /**
         * @brief Log a critical message
         * 
         * @param file File name
         * @param line Line number
         * @param message Log message
         */
        static void logCritical(const char* file, int line, const char* message);

    private:
        /**
         * @brief Logging levels
         */
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

        /**
         * @brief Logging level string representation
         */
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

        /**
         * @brief Log a message
         * 
         * @param logLevel Log level
         * @param file File name
         * @param line Line number
         * @param message Log message
         */
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
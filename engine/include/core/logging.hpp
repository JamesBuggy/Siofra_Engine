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
        template<typename T>
        static void logTrace(const char* file, int line, T message)
        {
            log(LogLevel::trace, file, line, message);
        }

        /**
         * @brief Log a debug message
         * 
         * @param file File name
         * @param line Line number
         * @param message Log message
         */
        template<typename T>
        static void logDebug(const char* file, int line, T message)
        {
            log(LogLevel::debug, file, line, message);
        }

        /**
         * @brief Log an informational message
         * 
         * @param file File name
         * @param line Line number
         * @param message Log message
         */
        template<typename T>
        static void logInfo(const char* file, int line, T message)
        {
            log(LogLevel::info, file, line, message);
        }

        /**
         * @brief Log a warning message
         * 
         * @param file File name
         * @param line Line number
         * @param message Log message
         */
        template<typename T>
        static void logWarning(const char* file, int line, T message)
        {
            log(LogLevel::warning, file, line, message);
        }

        /**
         * @brief Log an error message
         * 
         * @param file File name
         * @param line Line number
         * @param message Log message
         */
        template<typename T>
        static void logError(const char* file, int line, T message)
        {
            log(LogLevel::error, file, line, message);
        }

        /**
         * @brief Log a critical message
         * 
         * @param file File name
         * @param line Line number
         * @param message Log message
         */
        template<typename T>
        static void logCritical(const char* file, int line, T message)
        {
            log(LogLevel::critical, file, line, message);
        }

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
        template<typename T>
        static void log(LogLevel logLevel, const char* file, int line, T message)
        {
            int logLevelIndex = static_cast<int>(logLevel);
            std::cout << "[" << logLevelStrings[logLevelIndex] << "] "<< file << "(" << line << "): " << message << std::endl;
        }
    };
}

#ifdef _DEBUG
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
#include "core/logging.hpp"

namespace siofraEngine::core
{
    void Logger::logTrace(const char* file, int line, const char* message)
    {
        log(LogLevel::trace, file, line, message);
    }

    void Logger::logDebug(const char* file, int line, const char* message)
    {
        log(LogLevel::debug, file, line, message);
    }

    void Logger::logInfo(const char* file, int line, const char* message)
    {
        log(LogLevel::info, file, line, message);
    }

    void Logger::logWarning(const char* file, int line, const char* message)
    {
        log(LogLevel::warning, file, line, message);
    }

    void Logger::logError(const char* file, int line, const char* message)
    {
        log(LogLevel::error, file, line, message);
    }

    void Logger::logCritical(const char* file, int line, const char* message)
    {
        log(LogLevel::critical, file, line, message);
    }

    void Logger::log(LogLevel logLevel, const char* file, int line, const char* message)
    {
        int logLevelIndex = static_cast<int>(logLevel);
        std::cout << "[" << logLevelStrings[logLevelIndex] << "] "<< file << "(" << line << "): " << message << std::endl;
    }
}

#pragma once
#include <string>

#define LOG_FATAL(...) LogSystem::Fatal(__VA_ARGS__)
#define LOG_ERROR(...) LogSystem::Error(__VA_ARGS__)
#define LOG_WARN(...)  LogSystem::Warn(__VA_ARGS__)
#define LOG_INFO(...)  LogSystem::Info(__VA_ARGS__)
#define LOG_DEBUG(...) LogSystem::Debug(__VA_ARGS__)
#define LOG_TRACE(...) LogSystem::Trace(__VA_ARGS__)

class LogSystem
{
public:
    static void setSubstitutedValue(const std::string variable, const std::string value);

    // Kept for backward compatibility; we ignore the filename and just init logging.
    static void configureXml(const std::string filename);

    // Optional compat
    static void configureProperty(const std::string filename);
    static void configureBasic();

    // printf-style logging to avoid rewriting your existing calls
    static void Fatal(const char* fmt, ...);
    static void Error(const char* fmt, ...);
    static void Warn(const char* fmt, ...);
    static void Info(const char* fmt, ...);
    static void Debug(const char* fmt, ...);
    static void Trace(const char* fmt, ...);
};

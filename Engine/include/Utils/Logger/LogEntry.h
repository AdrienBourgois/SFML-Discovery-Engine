#pragma once

#include <chrono>
#include <source_location>

enum class ELogLevel : char
    {
        Debug,
        Info,
        Warning,
        Error,
        Critical
    };

struct LogEntry
{
    std::chrono::system_clock::time_point timestamp;
    ELogLevel level;
    std::string message;
    std::source_location sourceLocation;

    LogEntry(ELogLevel _lvl, const std::string& _msg, const std::source_location& _loc);

    std::string ToString() const;
    std::string GetFormattedTime() const;

    static constexpr std::string_view LevelToString(ELogLevel _level);
};
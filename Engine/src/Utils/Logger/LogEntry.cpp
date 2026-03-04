#include "Utils/Logger/LogEntry.h"

LogEntry::LogEntry(const ELogLevel _lvl, const std::string& _msg, const std::source_location& _loc)
: timestamp(std::chrono::system_clock::now()), level(_lvl), message(_msg), sourceLocation(_loc)
{}

std::string LogEntry::ToString() const
{
    return std::format("[{}][{}] {}", GetFormattedTime(), LevelToString(level), message);
}

std::string LogEntry::GetFormattedTime() const
{
    return std::format("{:%Y-%m-%d %H:%M:%S}", timestamp);
}

constexpr std::string_view LogEntry::LevelToString(const ELogLevel _level)
{
    switch (_level)
    {
    case ELogLevel::Debug:
        return "DEBUG";
    case ELogLevel::Info:
        return "INFO";
    case ELogLevel::Warning:
        return "WARNING";
    case ELogLevel::Error:
        return "ERROR";
    case ELogLevel::Critical:
        return "CRITICAL";
    default:
        return "UNKNOWN";
    }
}
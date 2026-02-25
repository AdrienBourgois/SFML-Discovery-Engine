#include "Modules/LoggerModule.h"

#include <chrono>
#include <cstdarg>
#include <iostream>
#include <print>

LoggerModule::LogEntry::LogEntry(const ELogLevel _lvl, const std::string& _msg, const std::source_location& _loc)
: timestamp(std::chrono::system_clock::now()), level(_lvl), message(_msg), sourceLocation(_loc)
{}

std::string LoggerModule::LogEntry::ToString() const
{
	return std::format("[{}][{}] {}", GetFormattedTime(), LevelToString(level), message);
}

std::string LoggerModule::LogEntry::GetFormattedTime() const
{
	return std::format("{:%Y-%m-%d %H:%M:%S}", timestamp);
}

constexpr std::string_view LoggerModule::LogEntry::LevelToString(const ELogLevel _level)
{
	switch (_level)
	{
	case ELogLevel::Debug:
		return "DEBUG";
	case ELogLevel::Verbose:
		return "VERBOSE";
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

LoggerModule::LoggerModule()
{
	file.open(defaultLogFileName, std::ios::out | std::ios::app);
}

LoggerModule::~LoggerModule()
{
	file.flush();
	file.close();
}

void LoggerModule::Flush()
{
	std::cout.flush();
	file.flush();
}

void LoggerModule::Log(const ELogLevel _level, const std::string& _text, const std::source_location& _loc)
{
	const LogEntry log(_level, _text, _loc);
	const std::string log_str = log.ToString();

	std::println("{}", log_str);

	if (file.is_open() && file.good())
		std::println(file, "{}", log_str);
}

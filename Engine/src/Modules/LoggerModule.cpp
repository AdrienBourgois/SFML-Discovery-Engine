#include "Modules/LoggerModule.h"

#include <chrono>
#include <cstdarg>
#include <iostream>
#include <sstream>

LoggerModule::LogEntry::LogEntry(const ELogLevel _lvl, const std::string& _msg) : timestamp(std::chrono::system_clock::now()), level(_lvl), message(_msg) {}

std::string LoggerModule::LogEntry::ToString() const
{
	std::ostringstream oss;
	oss << "[" << GetFormattedTime() << "][" << LevelToString(level) << "] " << message;
	return oss.str();
}

std::string LoggerModule::LogEntry::GetFormattedTime() const
{
	const std::time_t time_t_timestamp = std::chrono::system_clock::to_time_t(timestamp);
	std::tm tm_timestamp;
	localtime_s(&tm_timestamp, &time_t_timestamp);
	std::ostringstream time_stream;
	time_stream << std::put_time(&tm_timestamp, "%Y-%m-%d %H:%M:%S");
	return time_stream.str();
}

constexpr const char* LoggerModule::LogEntry::LevelToString(const ELogLevel _level)
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
	file.open("log.txt", std::ios::out | std::ios::app);
}

LoggerModule::~LoggerModule()
{
	file.close();
}

void LoggerModule::Log(const ELogLevel _level, const std::string& _text)
{
	const LogEntry log(_level, _text);
	const std::string log_str = log.ToString();
	std::cout << log_str << std::endl;
	file << log_str << std::endl;
	file.flush();
}

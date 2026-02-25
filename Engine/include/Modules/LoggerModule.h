#pragma once

#include <chrono>
#include <fstream>
#include <source_location>
#include <string>

#include "Module.h"

class LoggerModule final : public Module
{
public:
	enum class ELogLevel : char
	{
		Debug,
		Verbose,
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

	const std::string defaultLogFileName = "EngineLog.txt";

	LoggerModule();
	~LoggerModule() override;

	void Flush();

	inline void Log(ELogLevel _level, const std::string& _text, const std::source_location& _loc = std::source_location::current());

private:
	std::ofstream file;
};

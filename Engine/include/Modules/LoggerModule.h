#pragma once

#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>

#include "Module.h"

class LoggerModule final : public Module
{
public:
	enum class ELogLevel
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

		LogEntry(ELogLevel _lvl, const std::string& _msg);

		std::string ToString() const;
		std::string GetFormattedTime() const;

		static constexpr const char* LevelToString(ELogLevel _level);
	};

	LoggerModule();
	~LoggerModule() override;

	void Log(ELogLevel _level, const std::string& _text);

private:
	std::ofstream file;
};

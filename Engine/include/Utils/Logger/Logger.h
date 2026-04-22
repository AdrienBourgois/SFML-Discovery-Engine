#pragma once

#include <chrono>
#include <filesystem>
#include <fstream>
#include <source_location>
#include <string>

#include "LogEntry.h"

class Logger final
{
public:
    class LogFormat
    {
    public:
        std::string_view fmt;
        std::source_location loc;

        LogFormat(const char* _fmt, const std::source_location& _loc = std::source_location::current());
    };

private:
    static std::unique_ptr<Logger> instance;

    const std::filesystem::path defaultLogFolder = std::filesystem::temp_directory_path() / "SFML Discovery Engine" / "Logs";
    const std::string defaultLogFileName = "EngineLog.txt";

    std::ofstream file = std::ofstream();

    Logger();
    void OpenLogFile();
    void LogImpl(ELogLevel _level, const std::string& _text, const std::source_location& _loc);
    void Flush();

public:
    ~Logger();

    template<typename... Args>
    static void Log(ELogLevel _level, LogFormat _format, Args&&... _args);
};

#include "Logger.inl"

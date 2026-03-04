#include "Utils/Logger/Logger.h"

#include <iostream>
#include <print>

Logger::LogFormat::LogFormat(const char* _fmt, const std::source_location& _loc) : fmt(_fmt), loc(_loc) {}

std::unique_ptr<Logger> Logger::instance(new Logger);

Logger::Logger()
{
    OpenLogFile();
}

void Logger::OpenLogFile()
{
    if (!exists(defaultLogFolder))
    {
        create_directories(defaultLogFolder);
    }

    if (exists(defaultLogFolder / defaultLogFileName))
    {
        std::filesystem::rename(defaultLogFolder / defaultLogFileName, defaultLogFolder / "previousLog.txt");
    }

    try
    {
        file.open(defaultLogFolder / defaultLogFileName, std::ios::out | std::ios::app);
    }
    catch (std::exception& e)
    {
        std::print(std::cerr, "Failed to open log file: {}", e.what());
    }
}

void Logger::LogImpl(const ELogLevel _level, const std::string& _text, const std::source_location& _loc)
{
    const LogEntry log(_level, _text, _loc);
    const std::string log_str = log.ToString();

    std::println("{}", log_str);

    if (file.is_open() && file.good())
        std::println(file, "{}", log_str);
}

void Logger::Flush()
{
    std::cout.flush();
    file.flush();
}

Logger::~Logger()
{
    file.flush();
    file.close();
}

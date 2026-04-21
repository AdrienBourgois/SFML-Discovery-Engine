#pragma once

void Logger::Log(const ELogLevel _level, const LogFormat _format, auto&&... _args)
{
    instance->LogImpl(_level, std::vformat(_format.fmt, std::make_format_args(_args...)), _format.loc);
}

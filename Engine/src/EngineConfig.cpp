#include "EngineConfig.h"

const std::filesystem::path EngineConfig::TempDirectoryPath = std::filesystem::temp_directory_path() / "SFML Discovery Engine";

bool EngineConfig::ArgExists(const std::string& _arg) const
{
    return commandLineArgs.contains(_arg);
}

std::string EngineConfig::GetArg(const std::string& _arg) const
{
    if (const auto it = commandLineArgs.find(_arg); it != commandLineArgs.end())
        return it->second;

    return "";
}

bool EngineConfig::IsDebugMode() const
{
    return isDebugMode;
}

void EngineConfig::SetDebugMode(const bool _debug_mode)
{
    isDebugMode = _debug_mode;
}

bool EngineConfig::ToggleDebugMode()
{
    isDebugMode = !isDebugMode;
    return isDebugMode;
}

void EngineConfig::ParseCommandLineArguments(const int _argc, const char** _argv)
{
    commandLineArgs.clear();

    if (_argc <= 0)
        return;

    if (_argv && _argv[0])
        invokeCommand = _argv[0];

    std::string pending_key;

    for (int i = 1; i < _argc; ++i)
    {
        std::string token = _argv[i];

        if (!token.empty() && token.starts_with('-'))
        {
            // Strip all leading dashes
            size_t start = 0;
            while (start < token.size() && token[start] == '-')
                ++start;

            if (start >= token.size())
                continue;

            if (!pending_key.empty())
            {
                commandLineArgs.insert_or_assign(pending_key, "");
                pending_key.clear();
            }

            pending_key = token.substr(start);
        }
        else
        {
            if (!pending_key.empty())
            {
                commandLineArgs.insert_or_assign(pending_key, token);
                pending_key.clear();
            }
        }
    }

    if (!pending_key.empty())
    {
        commandLineArgs.insert_or_assign(pending_key, "");
        pending_key.clear();
    }
}

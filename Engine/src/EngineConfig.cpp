#include "EngineConfig.h"

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

void EngineConfig::SetCommandLineArgs(const int _argc, const char** _argv)
{
    commandLineArgs.clear();

    if (_argc <= 0)
        return;

    if (_argv && _argv[0])
        invokeCommand = _argv[0];

    std::string key;
    std::string value;

    for (int i = 1; i < _argc; ++i)
    {
        if (std::string arg = _argv[i]; arg.starts_with('-'))
        {
            if (!key.empty())
            {
                commandLineArgs.insert_or_assign(key, value);
                key.clear();
                value.clear();
            }

            key = arg.substr(1);
        }
        else
        {
            value = arg;
        }

        commandLineArgs.insert_or_assign(key, value);
    }
}



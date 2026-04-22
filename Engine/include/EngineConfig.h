#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <string_view>

class EngineConfig
{
public:
    static const std::filesystem::path TempDirectoryPath;

    static constexpr std::string_view AssetsFolderName = "Assets";
    static constexpr std::string_view EngineVersion = "0.1.0";

    struct ProjectConfig
    {
        std::filesystem::path projectRoot;
    };

    bool ArgExists(const std::string& _arg) const;
    std::string GetArg(const std::string& _arg) const;

    bool IsDebugMode() const;
    void SetDebugMode(bool _debug_mode);
    bool ToggleDebugMode();

private:
    friend class Engine;

    bool isDebugMode = false;

    std::optional<ProjectConfig> projectConfig;
    std::map<std::string, std::string> commandLineArgs;

    std::string invokeCommand;

    void ParseCommandLineArguments(int _argc, const char** _argv);
};

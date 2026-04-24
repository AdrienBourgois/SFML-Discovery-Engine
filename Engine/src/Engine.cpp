#include "Engine.h"

#include "SFML/Config.hpp"

#include "Utils/Logger/Logger.h"

Engine* Engine::GetInstance()
{
    if (instance == nullptr)
        instance = new Engine();

    return instance;
}

void Engine::Init(const int _argc, const char** _argv)
{
    Logger::Log(ELogLevel::Info, "SFML Discovery Engine - Version {}", EngineConfig::EngineVersion);
    Logger::Log(ELogLevel::Info, "Compiled on {} with SFML {}.{}.{}", __DATE__, SFML_VERSION_MAJOR, SFML_VERSION_MINOR, SFML_VERSION_PATCH);

    Logger::Log(ELogLevel::Info, "Engine Initialization Started");
    Logger::Log(ELogLevel::Info, "Working Directory : \"{}\"", std::filesystem::current_path().string());

    config.ParseCommandLineArguments(_argc, _argv);

    Logger::Log(ELogLevel::Info, "Engine Starting");

    moduleManager->Initialize();
}

void Engine::Run() const
{
    Logger::Log(ELogLevel::Info, "Engine Running");

    while (!quitRequested)
    {
        moduleManager->Tick();
    }

    moduleManager->Clean();

    Logger::Log(ELogLevel::Info, "Engine Closing");
}

void Engine::RequestQuit()
{
    Logger::Log(ELogLevel::Info, "Quit Requested");

    quitRequested = true;
}

bool Engine::IsQuitRequested() const
{
    return quitRequested;
}

ModuleManager* Engine::GetModuleManager() const
{
    return moduleManager;
}

EngineConfig& Engine::GetConfig()
{
    return config;
}

Engine* Engine::instance = nullptr;

Engine::Engine()
{
    moduleManager = new ModuleManager;
}

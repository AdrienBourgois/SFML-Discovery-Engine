#include "Engine.h"

#include "Utils/Logger/Logger.h"

Engine* Engine::GetInstance()
{
    if (instance == nullptr)
        instance = new Engine();

    return instance;
}

void Engine::Init(const int _argc, const char** _argv)
{
    Logger::Log(ELogLevel::Debug, "Engine Initialization Started");
    Logger::Log(ELogLevel::Debug, "Working Directory : \"{}\"", std::filesystem::current_path().string());

    config.ParseCommandLineArguments(_argc, _argv);

    moduleManager->CreateDefaultModules();
    moduleManager->Awake();
}

void Engine::Run() const
{
    Logger::Log(ELogLevel::Debug, "Engine Starting");

    moduleManager->Start();
    moduleManager->OnEnable();

    Logger::Log(ELogLevel::Debug, "Engine Running");

    while (!quitRequested)
    {
        moduleManager->Update();
        moduleManager->PreRender();
        moduleManager->Render();
        moduleManager->OnGUI();
        moduleManager->OnDebug();
        moduleManager->PostRender();
        moduleManager->Present();
    }

    Logger::Log(ELogLevel::Debug, "Engine Stopped");

    moduleManager->OnDisable();
    moduleManager->Destroy();
    moduleManager->Finalize();
}

void Engine::RequestQuit()
{
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

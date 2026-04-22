#pragma once

#include "EngineConfig.h"
#include "ModuleManager.h"

class Engine
{
public:
    static Engine* GetInstance();

    void Init(int _argc, const char** _argv);
    void Run() const;
    void RequestQuit();

    bool IsQuitRequested() const;

    ModuleManager* GetModuleManager() const;
    EngineConfig& GetConfig();

private:
    static Engine* instance;

    Engine();

    ModuleManager* moduleManager = nullptr;

    EngineConfig config;

    bool quitRequested = false;
};

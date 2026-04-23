#include "ModuleManager.h"

#include "Modules/AssetsModule.h"
#include "Modules/ImGuiModule.h"
#include "Modules/InputModule.h"
#include "Modules/SceneModule.h"
#include "Modules/TimeModule.h"
#include "Modules/WindowModule.h"

ModuleManager::~ModuleManager()
{
    Destroy();

    for (const Module* module : modules)
        delete module;
    modules.clear();

    for (const Module* module : pendingModules)
        delete module;
    pendingModules.clear();
}

void ModuleManager::CreateDefaultModules()
{
    CreateModule<TimeModule>();
    CreateModule<InputModule>();
    CreateModule<ImGuiModule>();
    CreateModule<WindowModule>();
    CreateModule<AssetsModule>();
    CreateModule<SceneModule>();
}

void ModuleManager::AddModule(Module* _module)
{
    if (_module->moduleManager == nullptr)
    {
        _module->moduleManager = this;
        _module->Awake();
        _module->OnEnable();
    }

    pendingModules.push_back(_module);
}

void ModuleManager::Initialize()
{
    CreateDefaultModules();

    FlushPending();
}

void ModuleManager::Tick()
{
    FlushPending();

    Update();
    PreRender();
    Render();
    OnGUI();
    OnDebug();
    PostRender();
    Present();
}

void ModuleManager::Clean()
{
    OnDisable();
    Destroy();
    Finalize();
}

void ModuleManager::Awake() const
{
    for (Module* module : modules)
    {
        module->Awake();
    }
}

void ModuleManager::Start() const
{
    for (Module* module : modules)
    {
        module->Start();
    }
}

void ModuleManager::Update() const
{
    for (Module* module : modules)
    {
        module->Update();
    }
}

void ModuleManager::PreRender() const
{
    for (Module* module : modules)
    {
        module->PreRender();
    }
}

void ModuleManager::Render() const
{
    for (Module* module : modules)
    {
        module->Render();
    }
}

void ModuleManager::OnGUI() const
{
    for (Module* module : modules)
    {
        module->OnGUI();
    }
}

void ModuleManager::PostRender() const
{
    for (Module* module : modules)
    {
        module->PostRender();
    }
}

void ModuleManager::OnDebug() const
{
    for (Module* module : modules)
    {
        module->OnDebug();
    }
}

void ModuleManager::OnDebugSelected() const
{
    for (Module* module : modules)
    {
        module->OnDebugSelected();
    }
}

void ModuleManager::Present() const
{
    for (Module* module : modules)
    {
        module->Present();
    }
}

void ModuleManager::OnEnable() const
{
    for (Module* module : modules)
    {
        module->OnEnable();
    }
}

void ModuleManager::OnDisable() const
{
    for (Module* module : modules)
    {
        module->OnDisable();
    }
}

void ModuleManager::Destroy() const
{
    for (Module* module : modules)
    {
        module->Destroy();
    }

    for (Module* module : pendingModules)
    {
        module->Destroy();
    }
}

void ModuleManager::Finalize() const
{
    for (Module* module : modules)
    {
        module->Finalize();
    }

    for (Module* module : pendingModules)
    {
        module->Finalize();
    }
}

void ModuleManager::FlushPending()
{
    for (Module* module : pendingModules)
    {
        modules.push_back(module);
        module->Start();
    }
    pendingModules.clear();
}

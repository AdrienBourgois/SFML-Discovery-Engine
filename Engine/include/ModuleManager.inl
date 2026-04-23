#pragma once
#include "Utils/Logger/Logger.h"

template <class T> requires IsModule<T>
T* ModuleManager::CreateModule()
{
    Logger::Log(ELogLevel::Debug, "Creating module: {}", typeid(T).name());

    T* module = new T();
    module->moduleManager = this;

    module->Awake();
    module->OnEnable();

    pendingModules.push_back(module);

    return module;
}

template <class T> requires IsModule<T>
T* ModuleManager::GetModule()
{
    for (Module* module : modules)
    {
        if (T* module_cast = dynamic_cast<T*>(module))
            return module_cast;
    }

    for (Module* module : pendingModules)
    {
        if (T* module_cast = dynamic_cast<T*>(module))
            return module_cast;
    }

    return nullptr;
}

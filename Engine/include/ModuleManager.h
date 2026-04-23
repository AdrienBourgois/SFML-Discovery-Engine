#pragma once

#include <vector>
#include "Core/Module.h"

class ModuleManager
{
public:
    ModuleManager() = default;
    ~ModuleManager();

    void CreateDefaultModules();
    void AddModule(Module* _module);

    void Initialize();
    void Tick();
    void Clean();

    void Awake() const;
    void Start() const;
    void Update() const;

    void PreRender() const;
    void Render() const;
    void OnGUI() const;
    void PostRender() const;
    void OnDebug() const;
    void OnDebugSelected() const;
    void Present() const;

    void OnEnable() const;
    void OnDisable() const;

    void Destroy() const;
    void Finalize() const;

    template <class T> requires IsModule<T>
    T* CreateModule();

    template <class T> requires IsModule<T>
    T* GetModule();

    void FlushPending();

private:
    std::vector<Module*> modules;

    std::vector<Module*> pendingModules;
};

#include "ModuleManager.inl"

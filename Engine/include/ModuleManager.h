#pragma once

#include <vector>
#include "Module.h"

class ModuleManager
{
public:
	ModuleManager() = default;
	~ModuleManager();

	void CreateDefaultModules();
	void AddModule(Module* _module);

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

	template<class T>
	T* CreateModule();

	template<class T>
	T* GetModule();

private:
	std::vector<Module*> modules;
};

#include "ModuleManager.inl"

#pragma once

#include "ModuleManager.h"

class Engine
{
public:
	static Engine* GetInstance();

	void Init() const;
	void Run() const;
	void Quit();

	ModuleManager* GetModuleManager() const;

private:
	static Engine* instance;

	Engine();

	ModuleManager* moduleManager = nullptr;

	bool shouldQuit = false;
};

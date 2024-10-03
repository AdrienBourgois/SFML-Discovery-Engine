#include "Engine.h"

Engine* Engine::instance = nullptr;

Engine* Engine::GetInstance()
{
	if (instance == nullptr)
		instance = new Engine();

	return instance;
}

void Engine::Init() const
{
	moduleManager->CreateDefaultModules();
	moduleManager->Awake();
}

void Engine::Run() const
{
	moduleManager->Start();
	moduleManager->OnEnable();

	while (!shouldQuit)
	{
		moduleManager->Update();
		moduleManager->PreRender();
		moduleManager->Render();
		moduleManager->OnGUI();
		moduleManager->OnDebug();
		moduleManager->PostRender();
		moduleManager->Present();
	}

	moduleManager->OnDisable();
	moduleManager->Destroy();
	moduleManager->Finalize();
}

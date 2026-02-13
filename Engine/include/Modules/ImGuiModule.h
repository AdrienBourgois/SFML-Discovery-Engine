#pragma once

#include "Module.h"
#include "SceneModule.h"
#include "TimeModule.h"
#include "WindowModule.h"

class ImGuiModule final : public Module
{
	void Start() override;
	void Update() override;
	void PostRender() override;
	void Finalize() override;

	void DisplayDebugWindow();
	void DisplayScenesList();
	void DisplayGameObjectsList(const Scene* _scene);
	void DisplayGameObjectItem(const GameObject* _game_object);

	void DisplayGameObjectAsSelected(const GameObject* _game_object);

	SceneModule* sceneModule = nullptr;
	WindowModule* windowModule = nullptr;
	TimeModule* timeModule = nullptr;

	GameObject* selectedGameObject = nullptr;

	bool displayDebugWindow = false;

protected:
	~ImGuiModule() override = default;
};

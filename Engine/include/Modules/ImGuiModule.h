#pragma once

#include <filesystem>

#include "EngineConfig.h"
#include "Core/Module.h"

// Forward declarations — only pointers stored; Scene/GameObject used only as ref params in declarations
class Scene;
class GameObject;
class SceneModule;
class TimeModule;
class WindowModule;

class ImGuiModule final : public Module
{
public:
    void Awake() override;
    void Start() override;
    void Update() override;
    void PostRender() override;
    void Finalize() override;
    void OnDebug() override;

    void DisplayDebugWindow();
    void DisplayScenesList();
    void DisplayGameObjectsList(const Scene& _scene);
    void DisplayGameObjectItem(const GameObject& _game_object);

    void DisplayGameObjectAsSelected(const GameObject& _game_object);

private:
    SceneModule* sceneModule = nullptr;
    WindowModule* windowModule = nullptr;
    TimeModule* timeModule = nullptr;

    GameObject* selectedGameObject = nullptr;

    std::filesystem::path iniPath = EngineConfig::TempDirectoryPath / "imgui.ini";

protected:
    ~ImGuiModule() override = default;
};

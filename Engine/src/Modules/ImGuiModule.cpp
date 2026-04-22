#include "Modules/ImGuiModule.h"

#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/Window/Event.hpp>

#include "EngineConfig.h"
#include "ModuleManager.h"

#include "Modules/InputModule.h"
#include "Modules/WindowModule.h"

void ImGuiModule::Awake()
{
    Module::Awake();
}

void ImGuiModule::Start()
{
    Module::Start();

    windowModule = moduleManager->GetModule<WindowModule>();
    timeModule = moduleManager->GetModule<TimeModule>();
    sceneModule = moduleManager->GetModule<SceneModule>();

    if (const bool init_result = ImGui::SFML::Init(*windowModule->GetWindow()); !init_result)
    {
        Logger::Log(ELogLevel::Error, "Failed to initialize ImGui-SFML");
    }
    else
    {
        ImGui::GetIO().IniFilename = nullptr;
        ImGui::LoadIniSettingsFromDisk(iniPath.string().c_str());
    }
}

void ImGuiModule::Update()
{
    Module::Update();

    const std::vector<sf::Event>& events = InputModule::GetEvents();

    for (const sf::Event& event : events)
        ImGui::SFML::ProcessEvent(*windowModule->GetWindow(), event);

    ImGui::SFML::Update(*windowModule->GetWindow(), timeModule->GetDeltaClock().getElapsedTime());

    if (InputModule::GetKeyDown(sf::Keyboard::Key::F1))
    {
        Engine::GetInstance()->GetConfig().ToggleDebugMode();
    }
}

void ImGuiModule::PostRender()
{
    Module::PostRender();

    ImGui::SFML::Render(*windowModule->GetWindow());
}

void ImGuiModule::Finalize()
{
    Module::Finalize();

    ImGui::SaveIniSettingsToDisk(iniPath.string().c_str());

    ImGui::SFML::Shutdown();
}

void ImGuiModule::OnDebug()
{
    Module::OnDebug();

    if (!Engine::GetInstance()->GetConfig().IsDebugMode())
        return;

    DisplayDebugWindow();
}

void ImGuiModule::DisplayDebugWindow()
{
    ImGui::Begin("World Debug");

    ImGui::SeparatorText("Scenes");

    DisplayScenesList();

    ImGui::SeparatorText("Selected GameObject");

    DisplayGameObjectAsSelected(*selectedGameObject);

    ImGui::End();
}

void ImGuiModule::DisplayScenesList()
{
    const auto& scenes = sceneModule->GetScenesList();

    for (auto&& scene : scenes)
    {
        DisplayGameObjectsList(*scene);
    }
}

void ImGuiModule::DisplayGameObjectsList(const Scene& _scene)
{
    constexpr ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

    if (ImGui::CollapsingHeader(_scene.GetName().c_str(), base_flags))
    {
        const auto& game_objects = _scene.GetGameObjects();
        for (const auto& game_object : game_objects)
        {
            DisplayGameObjectItem(*game_object);
        }
    }
}

void ImGuiModule::DisplayGameObjectItem(const GameObject& _game_object)
{
    if (ImGui::Selectable(_game_object.GetName().c_str(), selectedGameObject == &_game_object))
    {
        selectedGameObject = const_cast<GameObject*>(&_game_object);
    }
}

void ImGuiModule::DisplayGameObjectAsSelected(const GameObject& _game_object)
{
    if (selectedGameObject == nullptr)
    {
        ImGui::Text("No GameObject selected");
        return;
    }

    ImGui::Text("%s", _game_object.GetName().c_str());
}

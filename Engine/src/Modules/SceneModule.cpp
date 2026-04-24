#include "Modules/SceneModule.h"

#include <ranges>

#include "ModuleManager.h"
#include "Modules/TimeModule.h"
#include "Modules/WindowModule.h"

void SceneModule::Start()
{
    Module::Start();

    timeModule = moduleManager->GetModule<TimeModule>();
    windowModule = moduleManager->GetModule<WindowModule>();
}

void SceneModule::Render()
{
    Module::Render();

    for (const auto& scene : scenes)
    {
        scene->Render(windowModule->GetWindow());
    }
}

void SceneModule::Update()
{
    Module::Update();

    for (const auto& scene : scenes)
    {
        scene->Update(timeModule->GetDeltaTime());
    }
}

void SceneModule::Awake()
{
    Module::Awake();
}

void SceneModule::Destroy()
{
    Module::Destroy();

    for (const auto& scene : scenes)
    {
        scene->Destroy();
    }
}

void SceneModule::Finalize()
{
    Module::Finalize();

    for (const auto& scene : scenes)
    {
        scene->Finalize();
    }

    DeleteAllScenes();
    DeleteMarkedScenes();
}

void SceneModule::OnDebug()
{
    Module::OnDebug();

    for (const auto& scene : scenes)
    {
        scene->OnDebug();
    }
}

void SceneModule::OnDebugSelected()
{
    Module::OnDebugSelected();

    for (const auto& scene : scenes)
    {
        scene->OnDebugSelected();
    }
}

void SceneModule::OnDisable()
{
    Module::OnDisable();

    for (const auto& scene : scenes)
    {
        scene->OnDisable();
    }
}

void SceneModule::OnEnable()
{
    Module::OnEnable();

    for (const auto& scene : scenes)
    {
        scene->OnEnable();
    }
}

void SceneModule::OnGUI()
{
    Module::OnGUI();

    for (const auto& scene : scenes)
    {
        scene->OnGUI();
    }
}

void SceneModule::PostRender()
{
    Module::PostRender();

    for (const auto& scene : scenes)
    {
        scene->PostRender();
    }
}

void SceneModule::PreRender()
{
    Module::PreRender();

    for (const auto& scene : scenes)
    {
        scene->PreRender();
    }
}

void SceneModule::Present()
{
    Module::Present();

    for (const auto& scene : scenes)
    {
        scene->Present();
    }
}

Scene* SceneModule::GetSceneByName(const std::string& _scene_name) const
{
    auto condition = [_scene_name](const std::unique_ptr<Scene>& _scene)
    {
        return _scene->GetName() == _scene_name;
    };

    if (const auto it = std::ranges::find_if(scenes, condition); it != scenes.end())
    {
        return it->get();
    }

    Logger::Log(ELogLevel::Warning, "Scene with name {} not found.", _scene_name);

    return nullptr;
}

const std::vector<std::unique_ptr<Scene>>& SceneModule::GetScenesList() const
{
    return scenes;
}

bool SceneModule::DeleteSceneByName(const std::string& _scene_name) const
{
    if (Scene* scene = GetSceneByName(_scene_name))
    {
        scene->MarkForDeletion();
        return true;
    }

    return false;
}

void SceneModule::DeleteAllScenes() const
{
    for (const auto& scene : scenes)
    {
        scene->MarkForDeletion();
    }
}

void SceneModule::DeleteMarkedScenes()
{
    std::erase_if(scenes, [](const std::unique_ptr<Scene>& _scene)
    {
        if (!_scene->IsMarkedForDeletion())
            return false;

        _scene->Destroy();
        _scene->Finalize();

        Logger::Log(ELogLevel::Debug, "Scene {} deleted.", _scene->GetName());

        return true;
    });
}

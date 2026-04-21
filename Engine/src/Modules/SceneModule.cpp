#include "Modules/SceneModule.h"

#include <ranges>

#include "ModuleManager.h"

SceneModule::SceneModule() : Module()
{
}

SceneModule::~SceneModule()
{
    nextFrameScenesToDelete = scenes;
    ManageDeletedScenes();
}

void SceneModule::Start()
{
    Module::Start();

    timeModule = moduleManager->GetModule<TimeModule>();
    windowModule = moduleManager->GetModule<WindowModule>();

    for (const Scene* scene : scenes)
    {
        scene->Start();
    }
}

void SceneModule::Render()
{
    Module::Render();

    for (const Scene* scene : scenes)
    {
        scene->Render(windowModule->GetWindow());
    }
}

void SceneModule::Update()
{
    Module::Update();

    for (const Scene* scene : scenes)
    {
        scene->Update(timeModule->GetDeltaTime());
    }
}

void SceneModule::Awake()
{
    Module::Awake();

    for (const Scene* scene : scenes)
    {
        scene->Awake();
    }
}

void SceneModule::Destroy()
{
    Module::Destroy();

    for (const Scene* scene : scenes)
    {
        scene->Destroy();
    }
}

void SceneModule::Finalize()
{
    Module::Finalize();

    for (const Scene* scene : scenes)
    {
        scene->Finalize();
    }
}

void SceneModule::OnDebug()
{
    Module::OnDebug();

    for (const Scene* scene : scenes)
    {
        scene->OnDebug();
    }
}

void SceneModule::OnDebugSelected()
{
    Module::OnDebugSelected();

    for (const Scene* scene : scenes)
    {
        scene->OnDebugSelected();
    }
}

void SceneModule::OnDisable()
{
    Module::OnDisable();

    for (const Scene* scene : scenes)
    {
        scene->OnDisable();
    }
}

void SceneModule::OnEnable()
{
    Module::OnEnable();

    for (const Scene* scene : scenes)
    {
        scene->OnEnable();
    }
}

void SceneModule::OnGUI()
{
    Module::OnGUI();

    for (const Scene* scene : scenes)
    {
        scene->OnGUI();
    }
}

void SceneModule::PostRender()
{
    Module::PostRender();

    for (const Scene* scene : scenes)
    {
        scene->PostRender();
    }
}

void SceneModule::PreRender()
{
    Module::PreRender();

    for (const Scene* scene : scenes)
    {
        scene->PreRender();
    }
}

void SceneModule::Present()
{
    Module::Present();

    for (const Scene* scene : scenes)
    {
        scene->Present();
    }

    ManageDeletedScenes();
}

const std::vector<Scene*>& SceneModule::GetScenesList() const
{
    return scenes;
}

Scene* SceneModule::GetSceneByName(const std::string& _scene_name) const
{
    if (const auto it = std::ranges::find(scenes, _scene_name, &Scene::GetName); it != scenes.end())
    {
        return *it;
    }

    Logger::Log(ELogLevel::Warning, "Scene with name {} not found.", _scene_name);

    return nullptr;
}

bool SceneModule::DeleteSceneByName(const std::string& _scene_name)
{
    if (Scene* scene = GetSceneByName(_scene_name))
    {
        nextFrameScenesToDelete.push_back(scene);
        return true;
    }

    return false;
}

void SceneModule::DeleteAllScenes()
{
    nextFrameScenesToDelete.insert(nextFrameScenesToDelete.end(), scenes.begin(), scenes.end());
}

void SceneModule::ManageDeletedScenes()
{
    if (nextFrameScenesToDelete.empty())
        return;

    for (Scene* scenesToDelete : nextFrameScenesToDelete)
    {
        scenesToDelete->Disabled();
        scenesToDelete->Destroy();
        scenesToDelete->Finalize();

        std::erase(scenes, scenesToDelete);

        delete scenesToDelete;
    }

    nextFrameScenesToDelete.clear();
}

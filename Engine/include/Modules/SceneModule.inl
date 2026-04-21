#pragma once

template <typename T>
Scene* SceneModule::SetScene()
{
    nextFrameScene = CreateScene<T>();
    return nextFrameScene;
}

template <typename SceneType> requires IsScene<SceneType>
SceneType* SceneModule::CreateScene()
{
    SceneType* scene = new SceneType();
    scenes.push_back(scene);
    return scene;
}

template <typename SceneType> requires IsScene<SceneType>
Scene* SceneModule::GetSceneByType() const
{
    for (Scene* scene : scenes)
    {
        if (dynamic_cast<SceneType*>(scene))
        {
            return scene;
        }
    }

    Logger::Log(ELogLevel::Warning, "SceneModule::GetSceneByType - No scene of type " + std::string(typeid(SceneType).name()) + " found.");

    return nullptr;
}

template <typename SceneType> requires IsScene<SceneType>
bool SceneModule::DeleteSceneByType()
{
    if (Scene* scene = GetSceneByType<SceneType>())
    {
        nextFrameScenesToDelete.push_back(scene);
        return true;
    }

    return false;
}
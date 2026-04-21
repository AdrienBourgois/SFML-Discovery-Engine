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
    auto scene = std::make_unique<SceneType>();
    SceneType* rawPtr = scene.get();
    scenes.push_back(std::move(scene));
    return rawPtr;
}

template <typename SceneType> requires IsScene<SceneType>
Scene* SceneModule::GetSceneByType() const
{
    for (auto scene : scenes)
    {
        if (dynamic_cast<SceneType*>(scene))
        {
            return scene.get();
        }
    }

    Logger::Log(ELogLevel::Warning, "SceneModule::GetSceneByType - No scene of type " + std::string(typeid(SceneType).name()) + " found.");

    return nullptr;
}

template <typename SceneType> requires IsScene<SceneType>
bool SceneModule::DeleteSceneByType()
{
    if (auto* scene = GetSceneByType<SceneType>())
    {
        scene->MarkForDeletion();
        return true;
    }

    return false;
}
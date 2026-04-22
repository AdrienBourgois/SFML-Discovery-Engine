#pragma once

#include <memory>
#include <vector>

#include "Core/Module.h"
#include "Core/Scene.h"

#include "Modules/TimeModule.h"
#include "Modules/WindowModule.h"

class SceneModule final : public Module
{
public:
    void Start() override;
    void Render() override;
    void Update() override;
    void Awake() override;
    void Destroy() override;
    void Finalize() override;
    void OnDebug() override;
    void OnDebugSelected() override;
    void OnDisable() override;
    void OnEnable() override;
    void OnGUI() override;
    void PostRender() override;
    void PreRender() override;
    void Present() override;

    template <typename T>
    Scene* SetScene();

    const std::vector<std::unique_ptr<Scene>>& GetScenesList() const;

    template <typename SceneType> requires IsScene<SceneType>
    SceneType* CreateScene();

    template <typename SceneType> requires IsScene<SceneType>
    Scene* GetSceneByType() const;
    Scene* GetSceneByName(const std::string& _scene_name) const;

    template <typename SceneType> requires IsScene<SceneType>
    bool DeleteSceneByType();
    bool DeleteSceneByName(const std::string& _scene_name) const;

    void DeleteAllScenes() const;

private:
    void DeleteMarkedScenes();

    std::vector<std::unique_ptr<Scene>> scenes;

    WindowModule* windowModule = nullptr;
    TimeModule* timeModule = nullptr;

    Scene* nextFrameScene = nullptr;
};

#include "SceneModule.inl"

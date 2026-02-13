#pragma once
#include <vector>

#include "Module.h"
#include "Scene.h"
#include "TimeModule.h"
#include "WindowModule.h"

class SceneModule final : public Module
{
public:
	SceneModule();
	~SceneModule() override = default;

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

	template<typename T>
	Scene* SetScene(bool _replace_scenes = true);

	Scene* GetMainScene() const { return mainScene; }
	const std::vector<Scene*>& GetScenes() const;
	Scene* GetScene(const std::string& _scene_name) const;

private:
	std::vector<Scene*> scenes;
	Scene* mainScene = nullptr;

	WindowModule* windowModule = nullptr;
	TimeModule* timeModule = nullptr;
};

template<typename T>
Scene* SceneModule::SetScene(const bool _replace_scenes)
{
	if (_replace_scenes)
	{
		for (const Scene* scene : scenes)
		{
			delete scene;
		}
		scenes.clear();
	}

	Scene* scene = static_cast<Scene*>(new T());
	scenes.push_back(scene);

	if (_replace_scenes)
		mainScene = scene;

	return scene;
}

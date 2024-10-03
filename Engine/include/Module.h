#pragma once

class ModuleManager;

class Module
{
	friend class ModuleManager;

protected:
	virtual ~Module() = default;

public:
	virtual void Awake() {}
	virtual void Start() {}
	virtual void Update() {}

	virtual void PreRender() {}
	virtual void Render() {}
	virtual void OnGUI() {}
	virtual void PostRender() {}
	virtual void OnDebug() {}
	virtual void OnDebugSelected() {}
	virtual void Present() {}

	virtual void OnEnable() {}
	virtual void OnDisable() {}

	virtual void Destroy() {}
	virtual void Finalize() {}

protected:
	ModuleManager* moduleManager = nullptr;
};

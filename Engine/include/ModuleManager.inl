#pragma once

template<class T>
T* ModuleManager::CreateModule()
{
	T* module = new T();
	module->moduleManager = this;
	modules.push_back(module);
	return module;
}

template<class T>
T* ModuleManager::GetModule()
{
	for (Module*& module : modules)
	{
		if (T* module_cast = dynamic_cast<T*>(module))
		{
			return module_cast;
		}
	}
	return nullptr;
}

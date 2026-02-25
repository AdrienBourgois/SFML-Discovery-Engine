#pragma once

import std;

#include "Module.h"

#include "Resources/AResource.h"

class ResourcesModule final : public Module
{
protected:
	~ResourcesModule() override = default;

	template<typename ResourceType, typename... CtrParams>
	requires Resource<ResourceType>
	std::shared_ptr<ResourceType> LoadResource(const std::string& _path, CtrParams&&... _params)
	{
		using ResourceIterator = std::unordered_map<std::string, AResource*>::iterator;

		if (const ResourceIterator it = resources.find(_path); it != resources.end())
		{
			return static_cast<ResourceType*>(it->second);
		}

		AResource* resource = new AResource(_params...);

		if (resource->Load(_path))
		{
			resources[_path] = resource;
			return resource;
		}

		return nullptr;
	}

private:
	std::unordered_map<std::string, AResource*> resources;
};

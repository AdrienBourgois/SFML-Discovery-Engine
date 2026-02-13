#pragma once

#include <string>
#include <unordered_map>

#include "Module.h"

#include "Resources/ResourceBase.h"

class ResourcesModule final : public Module
{
protected:
	~ResourcesModule() override = default;

	template<typename T>
	ResourceBase<T>* LoadResource(const std::string& _path)
	{
		using ResourceIterator = std::unordered_map<std::string, AResource*>::iterator;

		if (const ResourceIterator it = resources.find(_path); it != resources.end())
		{
			return static_cast<T*>(it->second);
		}

		ResourceBase<T>* resource = new ResourceBase<T>;

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

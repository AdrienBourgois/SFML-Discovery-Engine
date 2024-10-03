#include "Resources/AResource.h"

const std::string AResource::AssetsFolderName = "Assets";

const std::filesystem::path AResource::AssetsFolderPath = std::filesystem::current_path() / AssetsFolderName;

AResource::AResource() {}

AResource::AResource(const AResource& _other) : path(_other.path), refCount(_other.refCount)
{
	IncreaseRefCount();
}

AResource::AResource(AResource&& _other) noexcept : path(std::move(_other.path)), refCount(_other.refCount)
{
	_other.refCount = nullptr;
}

AResource& AResource::operator=(const AResource& _other)
{
	if (this != &_other)
	{
		DecreaseRefCount();
		refCount = _other.refCount;
		path = _other.path;
		IncreaseRefCount();
	}
	return *this;
}

AResource& AResource::operator=(AResource&& _other) noexcept
{
	if (this != &_other)
	{
		DecreaseRefCount();
		refCount = _other.refCount;
		path = std::move(_other.path);
		_other.refCount = nullptr;
	}
	return *this;
}

AResource::~AResource()
{
	DecreaseRefCount();
}

bool AResource::Exists(const std::string& _name)
{
	const std::filesystem::path path = GetPathFromName(_name);
	return exists(path);
}

bool AResource::Load(const std::string& _path)
{
	return false;
}

void AResource::Unload() {}

unsigned int AResource::GetRefCount() const
{
	return refCount ? *refCount : 0;
}

void AResource::IncreaseRefCount() noexcept
{
	if (refCount)
		++(*refCount);
	else
		refCount = new unsigned int(1);
}

void AResource::DecreaseRefCount() noexcept
{
	if (refCount && --(*refCount) == 0)
	{
		Unload();
		delete refCount;
		refCount = nullptr;
	}
}

AResource::Path AResource::GetPathFromName(const std::string& _name)
{
	return AssetsFolderPath / _name;
}

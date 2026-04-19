#pragma once

#include <unordered_map>

#include "Module.h"

#include "Assets/Asset.h"

class AssetsModule final : public Module
{
public:
	using Path = std::filesystem::path;
	using AssetIterator = std::unordered_map<std::string, std::unique_ptr<Asset>>::iterator;

	AssetsModule();

	/**
	 * \brief Checks if a file exists.
	 * \param _path The path (absolute or relative to the Assets folder) of the file.
	 * \return True if the file exists, false otherwise.
	 */
	static bool Exists(const Path& _path);

	template<typename AssetType, typename... CtrParams> requires IsAsset<AssetType>
	AssetType* LoadAsset(const Path& _path, CtrParams&&... _params);

	template<typename AssetType> requires IsAsset<AssetType>
	AssetType* GetAsset(const Path& _path);

	void UnloadAll();

private:
	~AssetsModule() override;

	static Path AssetsFolderPath;

	std::unordered_map<std::string, std::unique_ptr<Asset>> assets;
};

#include "AssetsModule.inl"

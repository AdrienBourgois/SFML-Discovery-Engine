#pragma once

#include <unordered_map>

#include "Module.h"

#include "Assets/Asset.h"

class AssetsModule final : public Module
{
public:
	using Path = std::filesystem::path;

	AssetsModule();

	/**
	 * \brief Checks if a asset exists.
	 * \param _path The path (absolute or relative to the Assets folder) of the asset.
	 * \return True if the asset exists, false otherwise.
	 */
	static bool Exists(const Path& _path);

	template<typename AssetType, typename... CtrParams> requires IsAsset<AssetType>
	std::shared_ptr<AssetType> LoadAsset(const Path& _path, CtrParams&&... _params);

private:
	~AssetsModule() override = default;

	static Path AssetsFolderPath;

	std::unordered_map<std::string, std::shared_ptr<Asset>> assets;
};

#include "AssetsModule.inl"

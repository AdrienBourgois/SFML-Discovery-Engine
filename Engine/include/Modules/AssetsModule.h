#pragma once

#include <unordered_map>

#include "Module.h"

#include "Assets/Asset.h"

class AssetsModule final : public Module
{
public:
	using Path = std::filesystem::path;

	static constexpr std::string_view AssetsFolderName = "Assets";

	static const Path AssetsFolderPath;

	/**
	 * \brief Transforms the path to be relative to the project root folder / prefixed with Assets folder name.
	 * \param _path The path to be transformed.
	 * \return The relative path to the project root folder.
	 */
	static Path GetRelativeAssetPath(const Path& _path);

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


	std::unordered_map<std::string, std::shared_ptr<Asset>> assets;
};

#include "AssetsModule.inl"

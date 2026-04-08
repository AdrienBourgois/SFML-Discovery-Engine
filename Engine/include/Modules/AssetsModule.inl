#pragma once

#include <ostream>

#include "Utils/Logger/Logger.h"

template<typename AssetType, typename ... CtrParams> requires IsAsset<AssetType>
std::shared_ptr<AssetType> AssetsModule::LoadAsset(const std::filesystem::path& _path, CtrParams&&... _params)
{
    const std::filesystem::path relative_asset_path = relative(_path, AssetsFolderPath);
    const std::string relative_asset_path_string = relative_asset_path.string();

    using AssetIterator = std::unordered_map<std::string, std::shared_ptr<Asset>>::iterator;

    if (const AssetIterator it = assets.find(relative_asset_path_string); it != assets.end())
    {
        return std::static_pointer_cast<AssetType>(it->second);
    }

    /*if (!AssetType::GetSupportedExtensions().contains(relative_asset_path.extension().string()))
    {
        Logger::Log(ELogLevel::Error, "Unsupported file type: {}", relative_asset_path.string());
        return nullptr;
    }*/

    std::shared_ptr<AssetType> asset = std::make_shared<AssetType>(relative_asset_path, _params...);

    if (asset->Load(_path))
    {
        assets[relative_asset_path_string] = asset;
        return asset;
    }

    return nullptr;
}

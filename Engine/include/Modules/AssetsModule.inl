#pragma once

#include "Utils/Logger/Logger.h"

template<typename AssetType, typename ... CtrParams> requires IsAsset<AssetType>
std::shared_ptr<AssetType> AssetsModule::LoadAsset(const std::filesystem::path& _path, CtrParams&&... _params)
{
    const std::string path_string = _path.string();

    using AssetIterator = std::unordered_map<std::string, std::shared_ptr<Asset>>::iterator;

    if (const AssetIterator it = assets.find(path_string); it != assets.end())
    {
        return std::static_pointer_cast<AssetType>(it->second);
    }

    /*if (!AssetType::GetSupportedExtensions().contains(_path.extension().string()))
    {
        Logger::Log(ELogLevel::Error, "Unsupported file type: {}", _path.string());
        return nullptr;
    }*/

    std::shared_ptr<AssetType> asset = std::make_shared<AssetType>(path_string, _params...);

    if (asset->Load(_path))
    {
        assets[path_string] = asset;
        return asset;
    }

    return nullptr;
}

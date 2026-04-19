#pragma once

#include "Utils/Logger/Logger.h"

template<typename AssetType, typename ... CtrParams> requires IsAsset<AssetType>
AssetType* AssetsModule::LoadAsset(const std::filesystem::path& _path, CtrParams&&... _params)
{
    const std::string path_string = _path.string();

    if (const AssetIterator it = assets.find(path_string); it != assets.end())
    {
        Logger::Log(ELogLevel::Warning, "Asset already loaded, use GetAsset() next time : {}", path_string);

        return dynamic_cast<AssetType*>(it->second.get());
    }

    std::unique_ptr<AssetType> asset = std::make_unique<AssetType>(std::forward<CtrParams>(_params)...);

    if (asset->Load(_path))
    {
        AssetType* raw = asset.get();
        assets[path_string] = std::move(asset);
        return raw;
    }

    return nullptr;
}

template <typename AssetType> requires IsAsset<AssetType>
AssetType* AssetsModule::GetAsset(const Path& _path)
{
    const Path full_path = AssetsFolderPath / _path;

    const std::string path_string = full_path.string();

    if (const AssetIterator it = assets.find(path_string); it != assets.end())
    {
        return dynamic_cast<AssetType*>(it->second.get());
    }

    Logger::Log(ELogLevel::Error, "Asset not loaded: {}", path_string);

    return nullptr;
}
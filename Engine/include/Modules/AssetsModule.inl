#pragma once

#include "Utils/Logger/Logger.h"

template <typename AssetType, typename... CtrParams> requires IsAsset<AssetType>
AssetType* AssetsModule::LoadAsset(const std::filesystem::path& _path, CtrParams&&... _params)
{
    const std::filesystem::path path = _path;
    const std::filesystem::path full_path = assetsFolderPath / path;

    const std::string path_string = full_path.string();

    if (const AssetIterator it = assets.find(path_string); it != assets.end())
    {
        Logger::Log(ELogLevel::Warning, "Asset already loaded, use GetAsset() next time : {}", path_string);

        return dynamic_cast<AssetType*>(it->second.get());
    }

    if (!Exists(full_path))
    {
        Logger::Log(ELogLevel::Error, "Asset file does not exist: {}, resolved full path: {}", path_string,
                    full_path.string());
        return nullptr;
    }

    std::unique_ptr<AssetType> asset = std::make_unique<AssetType>(std::forward<CtrParams>(_params)...);

    if (asset->Load(full_path))
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
    const Path full_path = assetsFolderPath / _path;

    const std::string path_string = full_path.string();

    if (const AssetIterator it = assets.find(path_string); it != assets.end())
    {
        return dynamic_cast<AssetType*>(it->second.get());
    }

    Logger::Log(ELogLevel::Error, "Asset not loaded: {}", path_string);

    return nullptr;
}

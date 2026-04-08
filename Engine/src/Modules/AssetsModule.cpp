#include "Modules/AssetsModule.h"

const std::filesystem::path AssetsModule::AssetsFolderPath = std::filesystem::current_path() / AssetsFolderName;

std::filesystem::path AssetsModule::GetRelativeAssetPath(const Path& _path)
{
    if (_path.is_absolute())
        return relative(_path, AssetsFolderPath);

    return AssetsFolderPath / _path;
}

bool AssetsModule::Exists(const Path& _path)
{
    if (_path.is_absolute())
        return exists(_path);

    const std::filesystem::path path = GetRelativeAssetPath(_path);
    return exists(path);
}

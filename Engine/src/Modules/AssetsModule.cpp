#include "Modules/AssetsModule.h"

#include "Engine.h"
#include "EngineConfig.h"

std::filesystem::path AssetsModule::AssetsFolderPath;

AssetsModule::AssetsModule()
{
    AssetsFolderPath = std::filesystem::current_path() / EngineConfig::AssetsFolderName;
}

bool AssetsModule::Exists(const Path& _path)
{
    return exists(_path);
}

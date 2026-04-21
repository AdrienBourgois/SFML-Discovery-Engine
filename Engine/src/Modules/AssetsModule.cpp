#include "Modules/AssetsModule.h"

#include <ranges>

#include "Engine.h"
#include "EngineConfig.h"

void AssetsModule::UnloadAll()
{
    for (std::unique_ptr<Asset>& asset : assets | std::views::values)
    {
        asset->Unload();
        asset.reset();
    }

    assets.clear();
}

AssetsModule::~AssetsModule()
{
    UnloadAll();
}

std::filesystem::path AssetsModule::AssetsFolderPath;

AssetsModule::AssetsModule()
{
    AssetsFolderPath = std::filesystem::current_path() / EngineConfig::AssetsFolderName;
}

bool AssetsModule::Exists(const Path& _path)
{
    return exists(_path);
}

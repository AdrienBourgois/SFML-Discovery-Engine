#include "Modules/AssetsModule.h"

#include <ranges>

#include "Engine.h"
#include "EngineConfig.h"

AssetsModule::AssetsModule()
{
    assetsFolderPath = std::filesystem::current_path() / EngineConfig::AssetsFolderName;
}

void AssetsModule::Awake()
{
    Module::Awake();

    defaultFont = LoadAsset<Font>("Engine/Inter-VariableFont_opsz,wght.ttf");
}

bool AssetsModule::Exists(const Path& _path)
{
    return exists(_path);
}

Font* AssetsModule::GetDefaultFont() const
{
    return defaultFont;
}

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

std::filesystem::path AssetsModule::assetsFolderPath;

#include "Assets/Font.h"

#include "Utils/Logger/Logger.h"

bool Font::Load(const std::filesystem::path& _path)
{
    Asset::Load(_path);

    font = std::make_unique<sf::Font>();

    if (!font->openFromFile(path))
    {
        Logger::Log(ELogLevel::Error, "Failed to load font: {}", _path.string());
        return false;
    }

    Logger::Log(ELogLevel::Debug, "Font loaded successfully: {}", _path.string());

    return true;
}

bool Font::Unload()
{
    font.reset();

    return true;
}

const sf::Font& Font::GetSfmlAsset()
{
    return *font;
}

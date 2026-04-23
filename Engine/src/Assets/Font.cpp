#include "Assets/Font.h"

#include "Utils/Logger/Logger.h"

bool Font::Load(const std::filesystem::path& _path)
{
    Asset::Load(_path);

    font = std::make_unique<sf::Font>();

    return font->openFromFile(path);
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

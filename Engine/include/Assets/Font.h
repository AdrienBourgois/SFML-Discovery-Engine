#pragma once

#include "Assets/SfmlAsset.h"
#include "SFML/Graphics/Font.hpp"

class Font : public SfmlAsset<sf::Font>
{
public:
    bool Load(const std::filesystem::path& _path) override;

    bool Unload() override;

    const sf::Font& GetSfmlAsset() override;

private:
    std::unique_ptr<sf::Font> font;
};

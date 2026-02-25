#pragma once
#include <string>
#include <unordered_map>

#include <SFML/Graphics/Sprite.hpp>

class SpriteSheet
{
public:
    /*SpriteSheet* AddSprite(const std::string& _name, const sf::IntRect& _rect)
    {
        sprites.emplace(_name, sf::Sprite(*texture, _rect));
        return this;
    }

    SpriteSheet* AddSpriteSheet(const std::string& _base_name, const sf::IntRect& _rect, const sf::Vector2i& _size, const sf::Vector2i& _offset)
    {
        for (int y = 0; y < _size.y; y++)
        {
            for (int x = 0; x < _size.x; x++)
            {
                const sf::Vector2i position(_rect.position.x + x * _offset.x, _rect.position.y + y * _offset.y);
                const sf::Vector2i size(_offset.x, _offset.y);
                sprites.insert_or_assign(_base_name + "_" + std::to_string(x) + "_" + std::to_string(y), sf::Sprite(*texture, sf::IntRect(position, size)));
            }
        }
        return this;
    }

    std::unordered_map<std::string, sf::Sprite> sprites;

    sf::Texture* texture = nullptr;*/
};

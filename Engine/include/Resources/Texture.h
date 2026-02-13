#pragma once

#include <string>
#include <unordered_map>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "ResourceBase.h"

class Texture : public ResourceBase<sf::Texture>
{
public:
	explicit Texture(const std::string& _path);

	~Texture() override;

	Texture* AddSprite(const std::string& _name, const sf::IntRect& _rect);

	Texture* AddSpriteSheet(const std::string& _base_name, const sf::IntRect& _rect, const sf::Vector2i& _size, const sf::Vector2i& _offset);

private:
	std::unordered_map<std::string, sf::Sprite> sprites;
};

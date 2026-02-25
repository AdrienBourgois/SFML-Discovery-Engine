#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "AResource.h"

class Texture : public AResource
{
public:
	explicit Texture(const std::string& _path);

	~Texture() override;

private:
	std::unordered_map<std::string, sf::Sprite> sprites;

	sf::Texture* texture = nullptr;
};

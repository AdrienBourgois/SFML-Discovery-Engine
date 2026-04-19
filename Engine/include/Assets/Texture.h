#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Asset.h"

class Texture : public Asset
{
public:
	explicit Texture() = default;
	~Texture() override = default;

	bool Load(const std::filesystem::path& _path) override;

	bool Unload() override;

	sf::Sprite& GetSprite();

	const sf::Texture& GetTexture() const;

private:
	std::unique_ptr<sf::Texture> texture;

	std::optional<sf::Sprite> sprite;
};

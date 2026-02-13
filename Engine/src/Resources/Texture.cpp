#include "Resources/Texture.h"

Texture::Texture(const std::string& _path)
{
	data = new sf::Texture();
	if (!data->loadFromFile(_path))
	{
		// Handle error
	}
}

Texture::~Texture()
{
	delete data;
}

Texture* Texture::AddSprite(const std::string& _name, const sf::IntRect& _rect)
{
	sprites.emplace(_name, sf::Sprite(*data, _rect));
	return this;
}

Texture* Texture::AddSpriteSheet(const std::string& _base_name, const sf::IntRect& _rect, const sf::Vector2i& _size, const sf::Vector2i& _offset)
{
	for (int y = 0; y < _size.y; y++)
	{
		for (int x = 0; x < _size.x; x++)
		{
			const sf::Vector2i position(_rect.position.x + x * _offset.x, _rect.position.y + y * _offset.y);
			const sf::Vector2i size(_offset.x, _offset.y);
			sprites.insert_or_assign(_base_name + "_" + std::to_string(x) + "_" + std::to_string(y), sf::Sprite(*data, sf::IntRect(position, size)));
		}
	}
	return this;
}

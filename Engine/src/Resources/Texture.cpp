#include "Resources/Texture.h"

Texture::Texture(const std::string& _path)
{
	data = new sf::Texture();
	data->loadFromFile(_path);
}

Texture::~Texture()
{
	delete data;
}

Texture* Texture::AddSprite(const std::string& _name, const sf::IntRect& _rect)
{
	sprites.insert_or_assign(_name, sf::Sprite(*data, _rect));
	return this;
}

Texture* Texture::AddSprites(const std::string& _base_name, const sf::IntRect& _rect, const sf::Vector2i& _size, const sf::Vector2i& _offset)
{
	for (int y = 0; y < _size.y; y++)
	{
		for (int x = 0; x < _size.x; x++)
		{
			sprites.insert_or_assign(_base_name + "_" + std::to_string(x) + "_" + std::to_string(y), sf::Sprite(*data, sf::IntRect(_rect.left + x * _offset.x, _rect.top + y * _offset.y, _offset.x, _offset.y)));
		}
	}
	return this;
}

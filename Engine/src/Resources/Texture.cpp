#include "Resources/Texture.h"

Texture::Texture(const std::string& _path)
{
	texture = new sf::Texture();
	if (!texture->loadFromFile(_path))
	{
		// Handle error
	}
}

Texture::~Texture()
{
	delete texture;
}



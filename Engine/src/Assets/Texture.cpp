#include "Assets/Texture.h"

#include "Utils/Logger/Logger.h"

Texture::Texture(const std::filesystem::path& _path)
{
}

bool Texture::Load(const std::filesystem::path& _path)
{
	Asset::Load(_path);

	texture = std::make_unique<sf::Texture>();
	if (!texture->loadFromFile(_path))
	{
		Logger::Log(ELogLevel::Error, "Failed to load texture: {}", _path.string());
		return false;
	}

	Logger::Log(ELogLevel::Debug, "Texture loaded successfully: {}", _path.string());

	return true;
}

bool Texture::Unload()
{
	texture.reset();
	return true;
}

constexpr std::span<const std::string_view> Texture::GetSupportedExtensions() const
{
	return SupportedExtensions;
}

Texture::~Texture()
{
}

sf::Sprite& Texture::GetSprite()
{
	if (!sprite.has_value())
	{
		sprite = sf::Sprite(*texture);
	}

	return sprite.value();
}

const sf::Texture& Texture::GetTexture() const
{
	return *texture;
}


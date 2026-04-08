#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Asset.h"

class Texture : public Asset
{
public:
	explicit Texture(const std::filesystem::path& _path);

	bool Load(const std::filesystem::path& _path) override;

	bool Unload() override;

	constexpr std::span<const std::string_view> GetSupportedExtensions() const override;

	~Texture() override;

	sf::Sprite& GetSprite();

	const sf::Texture& GetTexture() const;

private:
	std::unique_ptr<sf::Texture> texture;

	std::optional<sf::Sprite> sprite;

	static constexpr std::array SupportedExtensions { std::string_view{".bmp"}, std::string_view{".png"}, std::string_view{".tga"}, std::string_view{".jpg"}, std::string_view{".gif"}, std::string_view{".psd"}, std::string_view{".hdr"}, std::string_view{".pic"}, std::string_view{".pnm"} };
};

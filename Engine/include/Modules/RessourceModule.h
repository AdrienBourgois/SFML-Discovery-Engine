#pragma once

#include <string>

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Module.h"

class RessourceModule final : public Module
{
public:
	/**
	 * \brief Default constructor.
	 */
	RessourceModule() = default;

	/**
	 * \brief Default destructor.
	 */
	~RessourceModule() = default;

	/**
	 * \brief Called when the module is initialized.
	 */
	void Awake() override;

	/**
	 * \brief Called once per frame to update the module.
	 */
	void Update() override;

	/**
	 * \brief Load a texture from a file.
	 * \param _path The path to the file.
	 * \return The loaded texture.
	 */
	sf::Texture LoadTexture(const std::string& _path);

	/**
	 * \brief Load a font from a file.
	 * \param _path The path to the file.
	 * \return The loaded font.
	 */
	sf::Font LoadFont(const std::string& _path);

	/**
	 * \brief Load a sound buffer from a file.
	 * \param _path The path to the file.
	 * \return The loaded sound buffer.
	 */
	sf::SoundBuffer LoadSoundBuffer(const std::string& _path);

	/**
	 * \brief Load a music from a file.
	 * \param _path The path to the file.
	 * \return The loaded music.
	 */
	sf::Music LoadMusic(const std::string& _path);

private:
};

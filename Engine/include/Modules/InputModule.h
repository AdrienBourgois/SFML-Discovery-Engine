#pragma once

#include <bitset>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Module.h"
#include "Maths/Vector2.h"

class InputModule final : public Module
{
public:
	void Start() override;
	void Update() override;

	static Maths::Vector2i GetMousePosition() { return mousePosition; }
	static Maths::Vector2i GetMouseDelta() { return mouseDelta; }

	static bool GetMouseButton(sf::Mouse::Button _button);
	static bool GetKey(sf::Keyboard::Key _key);

	static bool GetMouseButtonDown(sf::Mouse::Button _button);
	static bool GetKeyDown(sf::Keyboard::Key _key);

	static bool GetMouseButtonUp(sf::Mouse::Button _button);
	static bool GetKeyUp(sf::Keyboard::Key _key);

	static const std::vector<sf::Event>& GetEvents() { return events; }

private:
	sf::RenderWindow* window = nullptr;

	static Maths::Vector2i mousePosition;
	static Maths::Vector2i mouseDelta;

	static std::bitset<sf::Keyboard::KeyCount> keyDown;
	static std::bitset<sf::Keyboard::KeyCount> keyUp;
	static std::bitset<sf::Mouse::ButtonCount> mouseDown;
	static std::bitset<sf::Mouse::ButtonCount> mouseUp;

	static std::vector<sf::Event> events;
};

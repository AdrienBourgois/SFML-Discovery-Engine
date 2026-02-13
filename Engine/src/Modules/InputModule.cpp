#include "Modules/InputModule.h"

#include <imgui-SFML.h>
#include <SFML/Window/Event.hpp>

#include "Engine.h"
#include "ModuleManager.h"
#include "Modules/WindowModule.h"

void InputModule::Start()
{
	Module::Start();

	window = moduleManager->GetModule<WindowModule>()->GetWindow();
}

void InputModule::Update()
{
	Module::Update();

	events.clear();
	keyUp.reset();
	keyDown.reset();
	mouseDown.reset();
	mouseUp.reset();

	while (const std::optional event = window->pollEvent())
	{
		events.push_back(event.value());

		if (event->is<sf::Event::Closed>())
		{
			Engine::GetInstance()->Quit();
		}
		else if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>())
		{
			keyDown.set(static_cast<size_t>(key_pressed->code));
		}
		else if (const auto* key_released = event->getIf<sf::Event::KeyReleased>())
		{
			keyUp.set(static_cast<size_t>(key_released->code));
		}
		else if (const auto* mouse_button_pressed = event->getIf<sf::Event::MouseButtonPressed>())
		{
			mouseDown.set(static_cast<size_t>(mouse_button_pressed->button));
		}
		else if (const auto* mouse_button_released = event->getIf<sf::Event::MouseButtonReleased>())
		{
			mouseUp.set(static_cast<size_t>(mouse_button_released->button));
		}
	}

	const sf::Vector2i previous_mouse_position = sf::Vector2i(mousePosition);
	const sf::Vector2i new_mouse_position = sf::Mouse::getPosition(*window);

	mouseDelta = new_mouse_position - previous_mouse_position;
	mousePosition = new_mouse_position;
}

bool InputModule::GetMouseButton(const sf::Mouse::Button _button)
{
	return isButtonPressed(_button);
}

bool InputModule::GetKey(const sf::Keyboard::Key _key)
{
	return isKeyPressed(_key);
}

bool InputModule::GetMouseButtonDown(const sf::Mouse::Button _button)
{
	return mouseDown.test(static_cast<unsigned int>(_button));
}

bool InputModule::GetKeyDown(const sf::Keyboard::Key _key)
{
	return keyDown.test(static_cast<unsigned int>(_key));
}

bool InputModule::GetMouseButtonUp(const sf::Mouse::Button _button)
{
	return mouseUp.test(static_cast<unsigned int>(_button));
}

bool InputModule::GetKeyUp(const sf::Keyboard::Key _key)
{
	return keyUp.test(static_cast<unsigned int>(_key));
}

Maths::Vector2i InputModule::mousePosition = Maths::Vector2i::Zero;
Maths::Vector2i InputModule::mouseDelta = Maths::Vector2i::Zero;

std::vector<sf::Event> InputModule::events;

std::bitset<sf::Mouse::ButtonCount> InputModule::mouseDown;
std::bitset<sf::Mouse::ButtonCount> InputModule::mouseUp;
std::bitset<sf::Keyboard::KeyCount> InputModule::keyDown;
std::bitset<sf::Keyboard::KeyCount> InputModule::keyUp;

#include "Modules/WindowModule.h"

#include <iostream>

#include <SFML/Window/Event.hpp>

#include "Engine.h"

void WindowModule::Awake()
{
	Module::Awake();

	window = new sf::RenderWindow(sf::VideoMode({600, 600}), "SFML Discovery Engine");
}

void WindowModule::PreRender()
{
	Module::PreRender();

	window->clear(sf::Color::Black);
}

void WindowModule::Present()
{
	Module::Present();

	window->display();
}

void WindowModule::Destroy()
{
	Module::Destroy();

	window->close();
}

Maths::Vector2u WindowModule::GetSize() const
{
	return static_cast<Maths::Vector2u>(window->getSize());
}

void WindowModule::SetSize(const Maths::Vector2u _size) const
{
	window->setSize(sf::Vector2u(_size.x, _size.y));
}

void WindowModule::SetTitle(const std::string& _title) const
{
	window->setTitle(_title);
}

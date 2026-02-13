#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "ARenderedComponent.h"

class RectangleShapeRenderer : public ARenderedComponent
{
public:
	RectangleShapeRenderer();
	~RectangleShapeRenderer() override;

	void SetColor(const sf::Color& _color) { color = _color; }

	void Render(sf::RenderWindow* _window) override;
	void OnDebug() override;

private:
	sf::Color color = sf::Color::White;

	sf::RectangleShape* shape = nullptr;
};

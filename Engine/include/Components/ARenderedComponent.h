#pragma once

#include "Component.h"
#include "Maths/Vector2.h"

class ARenderedComponent : public Component
{
public:
	Maths::Vector2f GetSize() const { return size; }
	void SetSize(const Maths::Vector2f& _size) { size = _size; }

	void Render(sf::RenderWindow* _window) override;

protected:
	Maths::Vector2f size;
};

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Module.h"

#include "Maths/Vector2.h"

class WindowModule final : public Module
{
public:
	sf::RenderWindow* GetWindow() const { return window; }

	void Awake() override;
	void PreRender() override;
	void Present() override;
	void Destroy() override;

	Maths::Vector2u GetSize() const;
	void SetSize(Maths::Vector2u _size);

	void SetTitle(const std::string& _title) const;
	std::string GetTitle() const;

private:
	sf::RenderWindow* window = nullptr;
};

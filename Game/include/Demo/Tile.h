#pragma once
#include "Component.h"
#include "RectangleShapeRenderer.h"

class Tile : public Component
{
public:
    Tile(sf::Color _color, const Maths::Vector2i& _size);

    void Start() override;
    void Update(float _delta_time) override;

private:
    bool IsUnderCursor() const;

    RectangleShapeRenderer* rectangle = nullptr;
    sf::Color color;
    Maths::Vector2i size;
};

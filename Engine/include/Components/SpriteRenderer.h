#pragma once

#include "Assets/Texture.h"
#include "Components/ARenderedComponent.h"

class SpriteRenderer : public ARenderedComponent
{
public:
    explicit SpriteRenderer(Texture* _texture);

    ~SpriteRenderer() override = default;

    void Render(sf::RenderWindow* _window) override;

private:
    Texture* texture;
    sf::Rect<int> rect;
};

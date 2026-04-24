#include "Components/SpriteRenderer.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Core/GameObject.h"

SpriteRenderer::SpriteRenderer(Texture* _texture, const bool _set_pivot_in_center)
{
    texture = _texture;

    size = texture->GetTexture().getSize();

    if (_set_pivot_in_center)
        SetPivot(size / 2.0f);

    const Maths::Vector2i size_i = static_cast<Maths::Vector2i>(size);

    rect = sf::IntRect(static_cast<sf::Vector2i>(Maths::Vector2i::Zero), static_cast<sf::Vector2i>(size_i));
}

void SpriteRenderer::Render(sf::RenderWindow* _window)
{
    ARenderedComponent::Render(_window);

    sf::Sprite sprite(texture->GetTexture());

    sprite.setTextureRect(rect);

    const GameObject* owner = GetOwner();

    sprite.setPosition(static_cast<sf::Vector2f>(owner->GetPosition()));
    sprite.setOrigin(static_cast<sf::Vector2f>(GetPivot()));
    sprite.setRotation(owner->GetRotation());
    sprite.setScale(static_cast<sf::Vector2f>(owner->GetScale()));

    _window->draw(sprite);
}

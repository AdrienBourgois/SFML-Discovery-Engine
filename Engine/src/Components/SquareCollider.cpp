#include "Components/SquareCollider.h"

#include <imgui-SFML.h>

#include <SFML/Graphics/RectangleShape.hpp>

#include "Core/GameObject.h"
#include "Maths/Vector2.h"

namespace
{
    sf::FloatRect GetWorldBounds(const SquareCollider& _collider)
    {
        sf::RectangleShape rect_shape(static_cast<sf::Vector2f>(_collider.GetSize()));

        const GameObject* owner = _collider.GetOwner();

        rect_shape.setPosition(static_cast<sf::Vector2f>(owner->GetPosition()));
        rect_shape.setOrigin(static_cast<sf::Vector2f>(_collider.GetPivot()));
        rect_shape.setRotation(owner->GetRotation());
        rect_shape.setScale(static_cast<sf::Vector2f>(owner->GetScale()));

        return rect_shape.getGlobalBounds();
    }
}

SquareCollider::SquareCollider() = default;

SquareCollider::SquareCollider(const SpriteRenderer* _sprite)
{
    CopyFromSpriteRenderer(_sprite);
}

SquareCollider::~SquareCollider() = default;
void SquareCollider::CopyFromSpriteRenderer(const SpriteRenderer* _sprite)
{
    size = _sprite->GetSize();
    pivot = _sprite->GetPivot();
}

void SquareCollider::Render(sf::RenderWindow* _window)
{
    Component::Render(_window);

    if (Engine::GetInstance()->GetConfig().IsDebugMode())
    {
        const GameObject* owner = GetOwner();

        sf::RectangleShape rect_shape = sf::RectangleShape(sf::Vector2f(size));
        rect_shape.setOutlineColor(sf::Color::Green);
        rect_shape.setOutlineThickness(1.0f);
        rect_shape.setFillColor(sf::Color::Transparent);
        rect_shape.setPosition(static_cast<sf::Vector2f>(owner->GetPosition()));
        rect_shape.setOrigin(static_cast<sf::Vector2f>(GetPivot()));
        rect_shape.setRotation(owner->GetRotation());
        rect_shape.setScale(static_cast<sf::Vector2f>(owner->GetScale()));
        _window->draw(rect_shape);
    }
}

Maths::Vector2f SquareCollider::GetSize() const
{
    return size;
}

void SquareCollider::SetSize(const Maths::Vector2f& _size)
{
    size = _size;
}

float SquareCollider::GetWidth() const
{
    return size.x;
}

float SquareCollider::GetHeight() const
{
    return size.y;
}

void SquareCollider::SetWidth(const float _width)
{
    size.x = _width;
}

void SquareCollider::SetHeight(const float _height)
{
    size.y = _height;
}

Maths::Vector2f SquareCollider::GetPivot() const
{
    return pivot;
}

void SquareCollider::SetPivot(const Maths::Vector2f& _pivot)
{
    pivot = _pivot;
}

bool SquareCollider::IsColliding(const SquareCollider& _collider_a, const SquareCollider& _collider_b)
{
    const sf::FloatRect collider_a = GetWorldBounds(_collider_a);
    const sf::FloatRect collider_b = GetWorldBounds(_collider_b);

    const std::optional<sf::Rect<float>> intersection = collider_a.findIntersection(collider_b);
    return intersection.has_value();
}

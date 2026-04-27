#pragma once

#include "SpriteRenderer.h"

#include "Core/Component.h"

class SquareCollider : public Component
{
public:
    SquareCollider();
    explicit SquareCollider(const SpriteRenderer* _sprite);

    ~SquareCollider() override;

    void CopyFromSpriteRenderer(const SpriteRenderer* _sprite);

    void Render(sf::RenderWindow* _window) override;

    Maths::Vector2f GetSize() const;
    void SetSize(const Maths::Vector2f& _size);

    float GetWidth() const;
    float GetHeight() const;

    void SetWidth(float _width);
    void SetHeight(float _height);

    Maths::Vector2f GetPivot() const;
    void SetPivot(const Maths::Vector2f& _pivot);

    static bool IsColliding(const SquareCollider& _collider_a, const SquareCollider& _collider_b);

private:
    Maths::Vector2f size;
    Maths::Vector2f pivot;
};

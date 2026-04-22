#pragma once

#include "Core/Component.h"
#include "Maths/Vector2.h"

class ARenderedComponent : public Component
{
public:
    void Render(sf::RenderWindow* _window) override;

    const Maths::Vector2f& GetSize() const;
    void SetSize(const Maths::Vector2f& _size);

    const Maths::Vector2f& GetPivot() const;
    void SetPivot(const Maths::Vector2f& _pivot);

protected:
    Maths::Vector2f size;
    Maths::Vector2f pivot;

};

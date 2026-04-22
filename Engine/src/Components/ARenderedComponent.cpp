#include "Components/ARenderedComponent.h"
#include "Core/Component.h"

void ARenderedComponent::Render(sf::RenderWindow* _window)
{
    Component::Render(_window);
}

const Maths::Vector2f& ARenderedComponent::GetSize() const
{
    return size;
}

void ARenderedComponent::SetSize(const Maths::Vector2f& _size)
{
    size = _size;
}

const Maths::Vector2f& ARenderedComponent::GetPivot() const
{
    return pivot;
}

void ARenderedComponent::SetPivot(const Maths::Vector2f& _pivot)
{
    pivot = _pivot;
}

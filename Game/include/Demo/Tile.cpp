#include "Demo/Tile.h"

#include "InputModule.h"
#include "RectangleShapeRenderer.h"

Tile::Tile(const sf::Color _color, const Maths::Vector2i& _size): color(_color), size(_size)
{

}

void Tile::Start()
{
    rectangle = GetOwner()->CreateComponent<RectangleShapeRenderer>();
    rectangle->SetColor(color);
    rectangle->SetSize(Maths::Vector2f(size.x, size.y));
}

void Tile::Update(float _delta_time)
{
    if (InputModule::GetMouseButtonDown(sf::Mouse::Button::Left) && IsUnderCursor())
        GetOwner()->MarkForDeletion();
}

bool Tile::IsUnderCursor() const
{
    const Maths::Vector2i mouse_position = InputModule::GetMousePosition();
    const Maths::Vector2f mouse_position_f = Maths::Vector2f(mouse_position.x, mouse_position.y);

    const Maths::Vector2f& position = GetOwner()->GetPosition();
    const Maths::Vector2f& size = rectangle->GetSize();

    const sf::Rect<float> tile_rect = sf::Rect(static_cast<sf::Vector2f>(position), static_cast<sf::Vector2f>(size));

    return tile_rect.contains(static_cast<sf::Vector2f>(mouse_position_f));
}

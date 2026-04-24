#include "Demo/Tile.h"

#include "InputModule.h"
#include "RectangleShapeRenderer.h"
#include "Scene.h"
#include "TileSpawner.h"

Demo::Tile::Tile(const sf::Color _color, const Maths::Vector2i& _size): color(_color), size(_size)
{

}

void Demo::Tile::Start()
{
    rectangle = GetOwner()->CreateComponent<RectangleShapeRenderer>();
    rectangle->SetColor(color);
    rectangle->SetSize(Maths::Vector2f(size));
}

void Demo::Tile::Update(float _delta_time)
{
    if (InputModule::GetMouseButtonDown(sf::Mouse::Button::Left) && IsUnderCursor())
    {
        GameObject* tile_spawner = GetOwner()->GetScene()->FindGameObject("TileSpawner");
        if (tile_spawner)
        {
            tile_spawner->GetComponent<TileSpawner>()->TileRemoved();
            GetOwner()->MarkForDeletion();
        }
    }
}

bool Demo::Tile::IsUnderCursor() const
{
    const Maths::Vector2f mouse_position = static_cast<Maths::Vector2f>(InputModule::GetMousePosition());

    const Maths::Vector2f& position = GetOwner()->GetPosition();
    const Maths::Vector2f& size = rectangle->GetSize();

    const sf::Rect<float> tile_rect = sf::Rect(static_cast<sf::Vector2f>(position), static_cast<sf::Vector2f>(size));

    return tile_rect.contains(static_cast<sf::Vector2f>(mouse_position));
}

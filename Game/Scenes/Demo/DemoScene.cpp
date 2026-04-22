#include "DemoScene.h"

#include <chrono>
#include <cstdint>
#include <random>

#include "AssetsModule.h"
#include "RectangleShapeRenderer.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"
#include "WindowModule.h"

#include "Demo/Tile.h"

int RandomInt(const int _min, const int _max)
{
    thread_local std::mt19937_64 gen(static_cast<uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count()));

    std::uniform_real_distribution dist(static_cast<float>(_min), static_cast<float>(_max));
    return dist(gen);
}

Demo::DemoScene::DemoScene(): Scene("DemoScene")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* logo_texture = assets_module->LoadAsset<Texture>("logo.png");

    GameObject* const& logo = CreateGameObject("SFML Logo");
    logo->CreateComponent<SpriteRenderer>(logo_texture);

    for (int i = 0; i < 10; ++i)
    {
        CreateRandomTile();
    }
}

void Demo::DemoScene::CreateRandomTile()
{
    GameObject* game_object = CreateGameObject("Tile");

    sf::Color color = sf::Color(RandomInt(0, 255), RandomInt(0, 255), RandomInt(0, 255));

    const Maths::Vector2u window_size = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>()->GetSize();

    const int random_position_x = RandomInt(0, window_size.x);
    const int random_position_y = RandomInt(0, window_size.y);
    game_object->SetPosition(Maths::Vector2f(random_position_x, random_position_y));

    const int random_size = RandomInt(minSize, maxSize);
    game_object->CreateComponent<Tile>(color, Maths::Vector2i(random_size, random_size));
}
#include "Demo/TileSpawner.h"

#include <random>

#include "InputModule.h"
#include "Scene.h"
#include "Tile.h"
#include "TileCounter.h"
#include "WindowModule.h"

void Demo::TileSpawner::Start()
{
    Component::Start();

    for (int i = 0; i < 10; ++i)
    {
        SpawnTile();
    }
}

void Demo::TileSpawner::Update(float _delta_time)
{
    Component::Update(_delta_time);

    if (InputModule::GetKeyDown(sf::Keyboard::Key::Space))
    {
        SpawnTile();
    }
}

void Demo::TileSpawner::SpawnTile()
{
    Scene* scene = GetOwner()->GetScene();

    GameObject* game_object = scene->CreateGameObject("Tile");

    sf::Color color = sf::Color(RandomInt(0, 255), RandomInt(0, 255), RandomInt(0, 255));

    const Maths::Vector2u window_size = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>()->GetSize();

    const Maths::Vector2i random_position(RandomInt(0, window_size.x), RandomInt(0, window_size.y));

    game_object->SetPosition(Maths::Vector2f(random_position));

    const int random_size = RandomInt(minSize, maxSize);
    game_object->CreateComponent<Tile>(color, Maths::Vector2i(random_size, random_size));

    tileCount++;
    GetOwner()->GetComponent<TileCounter>()->SetTileCount(tileCount);
}

void Demo::TileSpawner::TileRemoved()
{
    tileCount--;
    GetOwner()->GetComponent<TileCounter>()->SetTileCount(tileCount);
}

int Demo::TileSpawner::RandomInt(const int _min, const int _max)
{
    thread_local std::mt19937_64 gen(static_cast<uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count()));

    std::uniform_real_distribution dist(static_cast<float>(_min), static_cast<float>(_max));
    return static_cast<int>(dist(gen));
}

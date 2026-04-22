#include "DemoScene.h"

#include "AssetsModule.h"
#include "RectangleShapeRenderer.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"

Demo::DemoScene::DemoScene(): Scene("DemoScene") {
    GameObject* player = CreateDummyGameObject("Player", 200.f, sf::Color::Red);
    player->CreateComponent<Player>();

    GameObject* enemy = CreateDummyGameObject("Enemy", 400.f, sf::Color::Blue);

    GameObject* enemy2 = CreateDummyGameObject("Enemy2", 0.f, sf::Color::Green);

    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* texture = assets_module->LoadAsset<Texture>("logo.png");

    player->CreateComponent<SpriteRenderer>(texture);
}

GameObject* Demo::DemoScene::CreateDummyGameObject(const std::string& _name, const float _position, const sf::Color _color) {
    GameObject* game_object = CreateGameObject(_name);
    game_object->SetPosition(Maths::Vector2f(_position, _position));

    SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
    square_collider->SetWidth(20.f);
    square_collider->SetHeight(20.f);

    RectangleShapeRenderer* shape_renderer = game_object->CreateComponent<RectangleShapeRenderer>();
    shape_renderer->SetColor(_color);
    shape_renderer->SetSize(Maths::Vector2f(200.f, 200.f));

    return game_object;
}
#include "DemoScene.h"

#include <random>

#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "TextRenderer.h"
#include "Texture.h"
#include "WindowModule.h"

#include "Demo/TileSpawner.h"

Demo::DemoScene::DemoScene(): Scene("DemoScene")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* logo_texture = assets_module->LoadAsset<Texture>("Engine/sfml_logo.png");

    GameObject* const& logo = CreateGameObject("SFML Logo");
    logo->CreateComponent<SpriteRenderer>(logo_texture, false);

    CreateGameObject("TileSpawner")->CreateComponent<TileSpawner>();

    TextRenderer* text_renderer = CreateGameObject("Text")->CreateComponent<TextRenderer>("Hello World!");
    text_renderer->SetColor(sf::Color::Yellow);
}

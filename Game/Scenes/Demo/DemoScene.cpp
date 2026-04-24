#include "DemoScene.h"

#include <random>

#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "TextRenderer.h"
#include "Texture.h"
#include "WindowModule.h"

#include "Demo/TileCounter.h"
#include "Demo/TileSpawner.h"

Demo::DemoScene::DemoScene(): Scene("DemoScene")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* logo_texture = assets_module->LoadAsset<Texture>("Engine/sfml_logo.png");

    GameObject* const& logo = CreateGameObject("SFML Logo");
    logo->CreateComponent<SpriteRenderer>(logo_texture, false);

    GameObject* tile_spawner = CreateGameObject("TileSpawner");
    tile_spawner->CreateComponent<TileSpawner>();
    tile_spawner->CreateComponent<TileCounter>();
    tile_spawner->SetPosition({200, 0});
}

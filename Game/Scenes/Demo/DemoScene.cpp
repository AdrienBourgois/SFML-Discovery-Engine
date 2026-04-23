#include "DemoScene.h"

#include <random>

#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"

#include "Demo/TileSpawner.h"

Demo::DemoScene::DemoScene(): Scene("DemoScene")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* logo_texture = assets_module->LoadAsset<Texture>("logo.png");

    GameObject* const& logo = CreateGameObject("SFML Logo");
    logo->CreateComponent<SpriteRenderer>(logo_texture);

    CreateGameObject("TileSpawner")->CreateComponent<TileSpawner>();
}

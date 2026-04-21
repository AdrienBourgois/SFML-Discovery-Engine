#include "Core/Scene.h"

#include <SFML/Graphics/RenderWindow.hpp>

Scene::Scene(const std::string& _name, const bool _enabled_at_start)
{
    name = _name;
    enabled = _enabled_at_start;
}

void Scene::Awake() const
{
    for (const auto& game_object : gameObjects)
    {
        game_object->Awake();
    }
}

void Scene::Start() const
{
    for (const auto& game_object : gameObjects)
    {
        game_object->Start();
    }
}

void Scene::PreRender() const
{
    for (const auto& game_object : gameObjects)
    {
        game_object->PreRender();
    }
}

void Scene::OnGUI() const
{
    for (const auto& game_object : gameObjects)
    {
        game_object->OnGUI();
    }
}

void Scene::PostRender() const
{
    for (const auto& game_object : gameObjects)
    {
        game_object->PostRender();
    }
}

void Scene::OnDebug() const
{
    for (const auto& game_object : gameObjects)
    {
        game_object->OnDebug();
    }
}

void Scene::OnDebugSelected() const
{
    for (const auto& game_object : gameObjects)
    {
        game_object->OnDebugSelected();
    }
}

void Scene::Present() const
{
    for (const auto& game_object : gameObjects)
    {
        game_object->Present();
    }
}

void Scene::OnEnable() const
{
    for (const auto& game_object : gameObjects)
    {
        game_object->OnEnable();
    }
}

void Scene::OnDisable() const
{
    for (const auto& game_object : gameObjects)
    {
        game_object->OnDisable();
    }
}

void Scene::Destroy() const
{
    for (const auto& game_object : gameObjects)
    {
        game_object->Destroy();
    }
}

void Scene::Finalize() const
{
    for (const auto& game_object : gameObjects)
    {
        game_object->Finalize();
    }
}

void Scene::Update(const float _delta_time) const
{
    for (const auto& game_object : gameObjects)
    {
        game_object->Update(_delta_time);
    }
}

void Scene::Render(sf::RenderWindow* _window) const
{
    for (const auto& game_object : gameObjects)
    {
        game_object->Render(_window);
    }
}

const std::string& Scene::GetName() const
{
    return name;
}

GameObject* Scene::CreateGameObject(const std::string& _name)
{
    auto game_object = std::make_unique<GameObject>();
    game_object->SetName(_name);
    GameObject* rawPtr = game_object.get();
    gameObjects.push_back(std::move(game_object));
    return rawPtr;
}

void Scene::DestroyGameObject(const GameObject* _game_object)
{
    std::erase_if(gameObjects, [_game_object](const std::unique_ptr<GameObject>& obj)
    {
        return obj.get() == _game_object;
    });
}

GameObject* Scene::FindGameObject(const std::string& _name) const
{
    for (const auto& game_object : gameObjects)
    {
        if (game_object->GetName() == _name)
        {
            return game_object.get();
        }
    }
    return nullptr;
}

const std::vector<std::unique_ptr<GameObject>>& Scene::GetGameObjects() const
{
    return gameObjects;
}

void Scene::Enable()
{
    if (!enabled)
    {
        enabled = true;
        OnEnable();
    }
}

void Scene::Disable()
{
    if (enabled)
    {
        enabled = false;
        OnDisable();
    }
}

bool Scene::IsEnabled() const
{
    return enabled;
}

void Scene::MarkForDeletion()
{
    markedForDeletion = true;
    Disable();
}

bool Scene::IsMarkedForDeletion() const
{
    return markedForDeletion;
}
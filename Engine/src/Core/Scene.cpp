#include "Core/Scene.h"

#include <SFML/Graphics/RenderWindow.hpp>

Scene::Scene(const std::string& _name)
{
    name = _name;
}

void Scene::Awake() const
{
    for (GameObject* const& game_object : gameObjects)
    {
        game_object->Awake();
    }
}

void Scene::Start() const
{
    for (GameObject* const& game_object : gameObjects)
    {
        game_object->Start();
    }
}

void Scene::PreRender() const
{
    for (GameObject* const& game_object : gameObjects)
    {
        game_object->PreRender();
    }
}

void Scene::OnGUI() const
{
    for (GameObject* const& game_object : gameObjects)
    {
        game_object->OnGUI();
    }
}

void Scene::PostRender() const
{
    for (GameObject* const& game_object : gameObjects)
    {
        game_object->PostRender();
    }
}

void Scene::OnDebug() const
{
    for (GameObject* const& game_object : gameObjects)
    {
        game_object->OnDebug();
    }
}

void Scene::OnDebugSelected() const
{
    for (GameObject* const& game_object : gameObjects)
    {
        game_object->OnDebugSelected();
    }
}

void Scene::Present() const
{
    for (GameObject* const& game_object : gameObjects)
    {
        game_object->Present();
    }
}

void Scene::OnEnable() const
{
    for (GameObject* const& game_object : gameObjects)
    {
        game_object->OnEnable();
    }
}

void Scene::OnDisable() const
{
    for (GameObject* const& game_object : gameObjects)
    {
        game_object->OnDisable();
    }
}

void Scene::Destroy() const
{
    for (GameObject* const& game_object : gameObjects)
    {
        game_object->Destroy();
    }
}

void Scene::Finalize() const
{
    for (GameObject* const& game_object : gameObjects)
    {
        game_object->Finalize();
    }
}

void Scene::Update(const float _delta_time) const
{
    for (GameObject* const& game_object : gameObjects)
    {
        game_object->Update(_delta_time);
    }
}

void Scene::Render(sf::RenderWindow* _window) const
{
    for (GameObject* const& game_object : gameObjects)
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
    const auto game_object = new GameObject();
    game_object->SetName(_name);
    gameObjects.push_back(game_object);
    return game_object;
}

void Scene::DestroyGameObject(const GameObject* _game_object)
{
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
    {
        if (*it == _game_object)
        {
            gameObjects.erase(it);
            delete _game_object;
            return;
        }
    }
}

GameObject* Scene::FindGameObject(const std::string& _name) const
{
    for (GameObject* const& game_object : gameObjects)
    {
        if (game_object->GetName() == _name)
        {
            return game_object;
        }
    }
    return nullptr;
}

const std::vector<GameObject*>& Scene::GetGameObjects() const
{
    return gameObjects;
}

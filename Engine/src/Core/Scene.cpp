#include "Core/Scene.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Core/GameObject.h"

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

void Scene::Update(const float _delta_time) const
{
    for (const auto& game_object : gameObjects)
    {
        if (!game_object->IsEnabled() || game_object->IsMarkedForDeletion())
            continue;

        game_object->Update(_delta_time);
    }
}

void Scene::PreRender() const
{
    for (const auto& game_object : gameObjects)
    {
        if (!game_object->IsEnabled() || game_object->IsMarkedForDeletion())
            continue;

        game_object->PreRender();
    }
}

void Scene::Render(sf::RenderWindow* _window) const
{
    for (const auto& game_object : gameObjects)
    {
        if (!game_object->IsEnabled() || game_object->IsMarkedForDeletion())
            continue;

        game_object->Render(_window);
    }
}

void Scene::OnGUI() const
{
    for (const auto& game_object : gameObjects)
    {
        if (!game_object->IsEnabled() || game_object->IsMarkedForDeletion())
            continue;

        game_object->OnGUI();
    }
}

void Scene::OnDebug() const
{
    for (const auto& game_object : gameObjects)
    {
        if (!game_object->IsEnabled() || game_object->IsMarkedForDeletion())
            continue;

        game_object->OnDebug();
    }
}

void Scene::OnDebugSelected() const
{
    for (const auto& game_object : gameObjects)
    {
        if (!game_object->IsEnabled() || game_object->IsMarkedForDeletion())
            continue;

        game_object->OnDebugSelected();
    }
}

void Scene::PostRender() const
{
    for (const auto& game_object : gameObjects)
    {
        if (!game_object->IsEnabled() || game_object->IsMarkedForDeletion())
            continue;

        game_object->PostRender();
    }
}

void Scene::Present()
{
    for (const auto& game_object : gameObjects)
    {
        game_object->Present();
    }

    DeleteMarkedGameObjects();

    FlushPending();
}

void Scene::FlushPending()
{
    while (!pendingGameObjects.empty())
    {
        std::vector<std::unique_ptr<GameObject>> batch = std::move(pendingGameObjects);

        for (auto& game_object : batch)
        {
            if (game_object->IsMarkedForDeletion())
            {
                game_object->Destroy();
                game_object->Finalize();
                continue;
            }

            game_object->FlushPending();

            game_object->Start();

            gameObjects.push_back(std::move(game_object));
        }
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

    for (const auto& game_object : pendingGameObjects)
    {
        game_object->Destroy();
    }
}

void Scene::Finalize()
{
    for (const auto& game_object : gameObjects)
    {
        game_object->Finalize();
    }

    for (const auto& game_object : pendingGameObjects)
    {
        game_object->Finalize();
    }
    pendingGameObjects.clear();

    DeleteMarkedGameObjects();
}

const std::string& Scene::GetName() const
{
    return name;
}

GameObject* Scene::CreateGameObject(const std::string& _name)
{
    auto game_object = std::make_unique<GameObject>();
    game_object->SetName(_name);
    game_object->SetScene(this);

    game_object->Awake();
    game_object->OnEnable();

    GameObject* raw_ptr = game_object.get();
    pendingGameObjects.push_back(std::move(game_object));
    return raw_ptr;
}

GameObject* Scene::FindGameObject(const std::string& _name) const
{
    for (const auto& game_object : gameObjects)
    {
        if (game_object->GetName() == _name)
            return game_object.get();
    }

    for (const auto& game_object : pendingGameObjects)
    {
        if (game_object->GetName() == _name)
            return game_object.get();
    }

    return nullptr;
}

const std::vector<std::unique_ptr<GameObject>>& Scene::GetGameObjects() const
{
    return gameObjects;
}

void Scene::DestroyGameObject(const GameObject* _game_object)
{
    for (const auto& game_object : gameObjects)
    {
        if (game_object.get() == _game_object)
        {
            game_object->MarkForDeletion();
            return;
        }
    }

    std::erase_if(pendingGameObjects, [_game_object](const std::unique_ptr<GameObject>& _obj)
    {
        if (_obj.get() != _game_object)
            return false;

        _obj->Disable();
        _obj->Destroy();
        _obj->Finalize();
        return true;
    });
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
    Disable();

    for (const auto& game_object : gameObjects)
        game_object->MarkForDeletion();

    for (const auto& game_object : pendingGameObjects)
        game_object->MarkForDeletion();

    markedForDeletion = true;
}

bool Scene::IsMarkedForDeletion() const
{
    return markedForDeletion;
}

void Scene::DeleteMarkedGameObjects()
{
    std::erase_if(gameObjects, [](const std::unique_ptr<GameObject>& _game_object)
    {
        if (!_game_object->IsMarkedForDeletion())
            return false;

        _game_object->Destroy();
        _game_object->Finalize();

        return true;
    });
}

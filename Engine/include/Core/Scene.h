#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Core/GameObject.h"

class Scene
{
public:
    explicit Scene(const std::string& _name);
    virtual ~Scene() = default;

    void Awake() const;
    void Start() const;
    void Update(float _delta_time) const;

    void PreRender() const;
    void Render(sf::RenderWindow* _window) const;
    void OnGUI() const;
    void OnDebug() const;
    void OnDebugSelected() const;
    void PostRender() const;
    void Present() const;

    void OnEnable() const;
    void OnDisable() const;

    void Destroy() const;
    void Finalize() const;

    const std::string& GetName() const;

    GameObject* CreateGameObject(const std::string& _name);
    void DestroyGameObject(const GameObject* _game_object);
    GameObject* FindGameObject(const std::string& _name) const;
    const std::vector<GameObject*>& GetGameObjects() const;

private:
    std::string name;
    std::vector<GameObject*> gameObjects;
};

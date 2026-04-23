#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Core/GameObject.h"

class GameObject;

class Scene
{
public:
    explicit Scene(const std::string& _name, bool _enabled_at_start = true);
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
    void Present();

    void FlushPending();

    void OnEnable() const;
    void OnDisable() const;

    void Destroy() const;
    void Finalize();

    const std::string& GetName() const;

    GameObject* CreateGameObject(const std::string& _name);

    GameObject* FindGameObject(const std::string& _name) const;
    const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const;

    void DestroyGameObject(const GameObject* _game_object);

    void Enable();
    void Disable();

    bool IsEnabled() const;

    void MarkForDeletion();
    bool IsMarkedForDeletion() const;

private:
    void DeleteMarkedGameObjects();

    std::string name;
    std::vector<std::unique_ptr<GameObject>> gameObjects;

    std::vector<std::unique_ptr<GameObject>> pendingGameObjects;

    bool enabled = true;

    bool markedForDeletion = false;
};

typedef std::unique_ptr<Scene> ScenePtr;

template<typename SceneType>
concept IsScene = std::derived_from<SceneType, Scene>;

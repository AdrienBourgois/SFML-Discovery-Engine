#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Core/Component.h"
#include "Maths/Vector2.h"

class Scene;
class Component;

class GameObject
{
public:
    GameObject() = default;
    ~GameObject();

    std::string GetName() const;

    Maths::Vector2<float> GetPosition() const;

    sf::Angle GetRotation() const;

    Maths::Vector2<float> GetScale() const;

    void SetName(const std::string& _name);

    void SetPosition(const Maths::Vector2<float>& _position);

    void SetRotation(const sf::Angle _rotation);

    void SetScale(const Maths::Vector2<float>& _scale);

    template <typename ComponentType, typename... Args> requires IsComponent<ComponentType>
    ComponentType* CreateComponent(Args&&... _args);

    template <typename ComponentType> requires IsComponent<ComponentType>
    ComponentType* GetComponent();

    std::vector<std::unique_ptr<Component>>& GetComponents();

    void Awake() const;
    void Start() const;
    void Update(float _delta_time) const;

    void PreRender() const;
    void Render(sf::RenderWindow* _window) const;
    void OnGUI() const;
    void PostRender() const;
    void OnDebug() const;
    void OnDebugSelected() const;
    void Present();

    void OnEnable() const;
    void OnDisable() const;

    void Destroy() const;
    void Finalize() const;

    void Enable();
    void Disable();
    bool IsEnabled() const;

    void MarkForDeletion();
    bool IsMarkedForDeletion() const;

    void SetScene(Scene* _scene);
    Scene* GetScene() const;

private:
    std::string name = "GameObject";

    bool enabled = true;
    bool markedForDeletion = false;

    Maths::Vector2<float> position = Maths::Vector2f::Zero;
    sf::Angle rotation = sf::degrees(0.f);
    Maths::Vector2<float> scale = Maths::Vector2f::One;

    std::vector<std::unique_ptr<Component>> components;

    Scene* scene = nullptr;

    void DeleteMarkedComponents();
};

#include "GameObject.inl"

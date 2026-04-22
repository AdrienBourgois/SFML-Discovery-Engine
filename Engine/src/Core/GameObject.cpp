#include "Core/GameObject.h"

#include <memory>
#include "Core/Scene.h"

GameObject::~GameObject()
{
    components.clear();
}

std::string GameObject::GetName() const {
    return name;
}

Maths::Vector2<float> GameObject::GetPosition() const {
    return position;
}

sf::Angle GameObject::GetRotation() const {
    return rotation;
}

Maths::Vector2<float> GameObject::GetScale() const {
    return scale;
}

void GameObject::SetName(const std::string& _name) {
    name = _name;
}

void GameObject::SetPosition(const Maths::Vector2<float>& _position) {
    position = _position;
}

void GameObject::SetRotation(const sf::Angle _rotation) {
    rotation = _rotation;
}

void GameObject::SetScale(const Maths::Vector2<float>& _scale) {
    scale = _scale;
}

std::vector<std::unique_ptr<Component>>& GameObject::GetComponents()
{
    return components;
}

void GameObject::Awake() const
{
    for (const auto& component : components)
    {
        component->Awake();
    }
}

void GameObject::Start() const
{
    for (const auto& component : components)
    {
        component->Start();
    }
}

void GameObject::Update(const float _delta_time) const
{
    for (const auto& component : components)
    {
        component->Update(_delta_time);
    }
}

void GameObject::PreRender() const
{
    for (const auto& component : components)
    {
        component->PreRender();
    }
}

void GameObject::Render(sf::RenderWindow* _window) const
{
    for (const auto& component : components)
    {
        component->Render(_window);
    }
}

void GameObject::OnGUI() const
{
    for (const auto& component : components)
    {
        component->OnGUI();
    }
}

void GameObject::PostRender() const
{
    for (const auto& component : components)
    {
        component->PostRender();
    }
}

void GameObject::OnDebug() const
{
    for (const auto& component : components)
    {
        component->OnDebug();
    }
}

void GameObject::OnDebugSelected() const
{
    for (const auto& component : components)
    {
        component->OnDebugSelected();
    }
}

void GameObject::Present()
{
    for (const auto& component : components)
    {
        component->Present();
    }

    DeleteMarkedComponents();
}

void GameObject::OnEnable() const
{
    for (const auto& component : components)
    {
        component->OnEnable();
    }
}

void GameObject::OnDisable() const
{
    for (const auto& component : components)
    {
        component->OnDisable();
    }
}

void GameObject::Destroy() const
{
    for (const auto& component : components)
    {
        component->Destroy();
    }
}

void GameObject::Finalize() const
{
    for (const auto& component : components)
    {
        component->Finalize();
    }
}

void GameObject::Enable()
{
    if (!enabled)
    {
        enabled = true;
        OnEnable();
    }
}

void GameObject::Disable()
{
    if (enabled)
    {
        enabled = false;
        OnDisable();
    }
}

bool GameObject::IsEnabled() const
{
    return enabled;
}

void GameObject::MarkForDeletion()
{
    Disable();
    markedForDeletion = true;
}

bool GameObject::IsMarkedForDeletion() const
{
    return markedForDeletion;
}

void GameObject::SetScene(Scene* _scene)
{
    scene = _scene;
}

Scene* GameObject::GetScene() const
{
    return scene;
}

void GameObject::DeleteMarkedComponents()
{
    std::erase_if(components, [](const std::unique_ptr<Component>& _component)
    {
        if (!_component->IsMarkedForDeletion())
            return false;

        _component->Destroy();
        _component->Finalize();

        return true;
    });
}

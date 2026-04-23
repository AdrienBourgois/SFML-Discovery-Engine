#include "Core/GameObject.h"

#include <memory>
#include "Core/Scene.h"

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
        if (!component->IsEnabled() || component->IsMarkedForDeletion())
            continue;

        component->Update(_delta_time);
    }
}

void GameObject::PreRender() const
{
    for (const auto& component : components)
    {
        if (!component->IsEnabled() || component->IsMarkedForDeletion())
            continue;

        component->PreRender();
    }
}

void GameObject::Render(sf::RenderWindow* _window) const
{
    for (const auto& component : components)
    {
        if (!component->IsEnabled() || component->IsMarkedForDeletion())
            continue;

        component->Render(_window);
    }
}

void GameObject::OnGUI() const
{
    for (const auto& component : components)
    {
        if (!component->IsEnabled() || component->IsMarkedForDeletion())
            continue;

        component->OnGUI();
    }
}

void GameObject::PostRender() const
{
    for (const auto& component : components)
    {
        if (!component->IsEnabled() || component->IsMarkedForDeletion())
            continue;

        component->PostRender();
    }
}

void GameObject::OnDebug() const
{
    for (const auto& component : components)
    {
        if (!component->IsEnabled() || component->IsMarkedForDeletion())
            continue;

        component->OnDebug();
    }
}

void GameObject::OnDebugSelected() const
{
    for (const auto& component : components)
    {
        if (!component->IsEnabled() || component->IsMarkedForDeletion())
            continue;

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

    for (auto& component : pendingComponents)
    {
        if (component->IsMarkedForDeletion())
        {
            component->Destroy();
            component->Finalize();
            continue;
        }

        component->Start();
        components.push_back(std::move(component));
    }
    pendingComponents.clear();
}

void GameObject::FlushPending()
{
    for (auto& component : pendingComponents)
    {
        if (component->IsMarkedForDeletion())
        {
            component->Destroy();
            component->Finalize();
            continue;
        }

        components.push_back(std::move(component));
    }
    pendingComponents.clear();
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

    for (const auto& component : pendingComponents)
    {
        component->Destroy();
    }
}

void GameObject::Finalize()
{
    for (const auto& component : components)
    {
        component->Finalize();
    }

    for (const auto& component : pendingComponents)
    {
        component->Finalize();
    }
    pendingComponents.clear();

    DeleteMarkedComponents();
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

    for (const auto& component : components)
        component->MarkForDeletion();

    for (const auto& component : pendingComponents)
        component->MarkForDeletion();

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

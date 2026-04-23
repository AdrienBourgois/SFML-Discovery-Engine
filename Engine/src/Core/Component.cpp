#include "Core/Component.h"

void Component::Awake() {}
void Component::Start() {}
void Component::Update(float _delta_time) {}
void Component::PreRender() {}
void Component::Render(sf::RenderWindow* _window) {}
void Component::OnGUI() {}
void Component::PostRender() {}
void Component::OnDebug() {}
void Component::OnDebugSelected() {}
void Component::Present() {}
void Component::OnEnable() {}
void Component::OnDisable() {}
void Component::Destroy() {}
void Component::Finalize() {}

GameObject* Component::GetOwner() const
{
    return owner;
}

void Component::SetOwner(GameObject* _owner)
{
    owner = _owner;
}

bool Component::IsEnabled() const
{
    return enabled;
}

void Component::Enable()
{
    if (!enabled)
    {
        enabled = true;
        OnEnable();
    }
}

void Component::Disable()
{
    if (enabled)
    {
        enabled = false;
        OnDisable();
    }
}

bool Component::IsMarkedForDeletion() const
{
    return markedForDeletion;
}

void Component::MarkForDeletion()
{
    Disable();

    markedForDeletion = true;
}
